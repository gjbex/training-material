program svd
use blacs_matrices

implicit none

include 'mpif.h'

integer :: argc
character(len=1024) :: argv
logical :: is_verbose, do_check
integer :: nr_vecs, vec_len, row_block, col_block
integer, parameter :: local_size = 500000000
double precision, dimension(:, :), allocatable :: local_storage, local_u, &
                                                  local_vt
integer, dimension(DLEN_) :: storage_desc, u_desc, vt_desc
integer :: my_id, context, info, nr_procs, nr_proc_rows, nr_proc_cols, &
           my_proc_row, my_proc_col, local_nr_vecs, local_vec_len, &
           local_rows, local_cols, &
           vec_nr, local_vec_nr, i, local_i, vec_nr_1, vec_nr_2, ierror
double precision :: norm2, dot, dot_pdgemm, alpha
double precision :: start_time, end_time
double precision, allocatable, dimension(:) :: vector
integer :: lwork
double precision, allocatable, dimension(:) :: singular_values, work
integer :: seed_size
integer, allocatable, dimension(:) :: seeds

call blacs_initialize(my_id, context, nr_procs)
call determine_topology(nr_proc_rows, nr_proc_cols)
call blacs_set_topology(my_id, context, nr_proc_rows, nr_proc_cols, 'R', &
                        my_proc_row, my_proc_col)

call random_seed(size=seed_size)
allocate(seeds(seed_size))
do i = 1, seed_size
    seeds(i) = my_id
end do
call random_seed(put=seeds)

argc = command_argument_count()
if (argc >= 2) then
    call get_command_argument(1, argv)
    read (argv, *), nr_vecs
    call get_command_argument(2, argv)
    read (argv, *), vec_len
else
    nr_vecs = 5
    vec_len = 6
end if
if (argc >= 4) then
    call get_command_argument(3, argv)
    read (argv, *), row_block
    call get_command_argument(4, argv)
    read (argv, *), col_block
else
    row_block = 100
    col_block = 100
end if
if (argc >= 5) then
    is_verbose = .TRUE.
else
    is_verbose = .FALSE.
end if

if (my_id == 0) then
    print 1021, nr_vecs, vec_len
    1021 format(1X, I6, ' vectors, ', I6, ' components')
    print 1022, row_block, col_block
    1022 format(1X, 'block: ', I6, ' x ', I6)
    print 1023, nr_proc_rows, nr_proc_cols
    1023 format(1X, 'processors: ', I2, ' x ', I2)
end if

local_nr_vecs = compute_dim(nr_vecs, col_block, nr_proc_cols, my_proc_col)
local_vec_len = compute_dim(vec_len, row_block, nr_proc_rows, my_proc_row)
allocate(local_storage(local_vec_len, local_nr_vecs))
if (is_verbose) print 1015, my_proc_row, my_proc_col, &
                            local_nr_vecs, local_vec_len, row_block, col_block
1015 format(1X, '[', I2, ',', I2, ']: ', I6, ' vecs, ', I6, ' components', &
            ', block size = ', I4, ' x ', I4)
call DESCINIT(storage_desc, vec_len, nr_vecs, row_block, col_block, &
              0, 0, context, local_vec_len, info)
if (is_verbose) call MPI_BARRIER(MPI_COMM_WORLD, ierror)

! initialize vectors
call MPI_BARRIER(MPI_COMM_WORLD, ierror)
start_time = MPI_WTIME()
do vec_nr = 1, nr_vecs
    if (is_mine(col_block, nr_proc_cols, my_proc_col, vec_nr)) then
        local_vec_nr = g_to_l_coord(col_block, nr_proc_cols, vec_nr)
        do i = 1, vec_len
            if (is_mine(row_block, nr_proc_rows, my_proc_row, i)) then
                local_i = g_to_l_coord(row_block, nr_proc_rows, i)
                if (is_verbose) print 1012, my_proc_row, my_proc_col, &
                                            i, vec_nr, local_i, local_vec_nr
                1012 format(1X, '[', I1, ',', I1, ']: ', I1, ',', I1, &
                            ' -> ', I1, ',', I1)
                call random_number(alpha)
                local_storage(local_i, local_vec_nr) = alpha
            end if
        end do
    end if
end do
call MPI_BARRIER(MPI_COMM_WORLD, ierror)
end_time = MPI_WTIME()
if (my_id == 0) print 10000, end_time - start_time
10000 format(1X, 'matrix initialization in ', F15.6, ' seconds')

if (is_verbose) call MPI_BARRIER(MPI_COMM_WORLD, ierror)

! print matrix to stdout to make sure  it was initialized as expected
if (is_verbose) then
    allocate(vector(vec_len))
    do vec_nr = 1, nr_vecs
        if (my_id == 0) print 1013, vec_nr
        1013 format(1X, 'vector ', I6, ':')
        do i = 1, vec_len
            call PDELGET('A', ' ', alpha, local_storage, i, vec_nr, storage_desc)
            vector(i) = alpha
        end do
        if (my_id == 0) print *, vector
    end do
    deallocate(vector)
end if

! compute the singular value decomposition using the appropriate Scalapack call
call MPI_BARRIER(MPI_COMM_WORLD, ierror)
start_time = MPI_WTIME()
allocate(singular_values(min(vec_len, nr_vecs)))
local_rows = compute_dim(vec_len, row_block, nr_proc_rows, my_proc_row)
local_cols = compute_dim(vec_len, col_block, nr_proc_cols, my_proc_col)
allocate(local_u(local_rows, local_cols))
call DESCINIT(u_desc, vec_len, vec_len, row_block, col_block, &
              0, 0, context, local_rows, info)
local_rows = compute_dim(nr_vecs, row_block, nr_proc_rows, my_proc_row)
local_cols = compute_dim(nr_vecs, col_block, nr_proc_cols, my_proc_col)
allocate(local_vt(local_rows, local_cols))
call DESCINIT(vt_desc, nr_vecs, nr_vecs, row_block, col_block, &
              0, 0, context, local_rows, info)
lwork = -1
allocate(work(1))
call pdgesvd('V', 'V', vec_len, nr_vecs, local_storage, 1, 1, storage_desc, &
                       singular_values,  local_u, 1, 1, u_desc, &
                                         local_vt, 1, 1, vt_desc, &
             work, lwork, info)
lwork = work(1)
deallocate(work)
allocate(work(lwork))
call pdgesvd('V', 'V', vec_len, nr_vecs, local_storage, 1, 1, storage_desc, &
                       singular_values,  local_u, 1, 1, u_desc, &
                                         local_vt, 1, 1, vt_desc, &
             work, lwork, info)
deallocate(work)
call MPI_BARRIER(MPI_COMM_WORLD, ierror)
end_time = MPI_WTIME()
if (my_id == 0) print 10003, end_time - start_time
10003 format(1X, 'pdgesvd computed in ', F15.6, ' seconds')

if (is_verbose) then
    if (my_id == 0) print *, 'U'
    allocate(vector(vec_len))
    do vec_nr = 1, vec_len
        do i = 1, vec_len
            call PDELGET('A', ' ', alpha, local_u, i, vec_nr, u_desc)
            vector(i) = alpha
        end do
        if (my_id == 0) print *, vector
    end do
    deallocate(vector)
end if
if (is_verbose .and. my_id == 0) then
    print *, 'singular values:'
    print *, singular_values
end if
if (is_verbose) then
    if (my_id == 0) print *, 'V^t'
    allocate(vector(nr_vecs))
    do vec_nr = 1, nr_vecs
        do i = 1, nr_vecs
            call PDELGET('A', ' ', alpha, local_vt, i, vec_nr, vt_desc)
            vector(i) = alpha
        end do
        if (my_id == 0) print *, vector
    end do
    deallocate(vector)
end if

deallocate(local_storage)
deallocate(local_u)
deallocate(local_vt)

call BLACS_EXIT(0)

end program svd

