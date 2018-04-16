program diffusion
use, intrinsic :: iso_fortran_env, only : dp => REAL64, error_unit
use :: mpi
implicit none
integer, parameter :: MEM_ALLOC_ERR = 1
integer, parameter :: default_n = 5, nr_dims = 2, nr_iters = 500
real(kind=dp), parameter :: tol = 1.0e-4_dp
integer :: ierr, iter_nr, n, comm_rank, comm_size
real(Kind=dp), dimension(:, :), allocatable :: new_temp, temp
character(len=1024) :: buffer
integer, dimension(nr_dims) :: dims
logical, dimension(nr_dims) :: periodic
logical :: reorder
integer :: cart_comm, row_type, col_type
real(kind=dp) :: delta, avg_temp

! setup MPI and get size and initial rank
call MPI_Init(ierr)
call MPI_Comm_size(MPI_COMM_WORLD, comm_size, ierr)
call MPI_Comm_rank(MPI_COMM_WORLD, comm_rank, ierr)

! setup Carthesian communicator
dims = 0
periodic = .true.
reorder = .true.
call MPI_Dims_create(comm_size, nr_dims, dims, ierr)
call MPI_Cart_create(MPI_COMM_WORLD, nr_dims, dims, periodic, reorder, &
                     cart_comm, ierr)
call MPI_Comm_rank(cart_comm, comm_rank, ierr)

! rank 0 handles command line arguments, and broadcasts them to other
! ranks
if (comm_rank == 0) then
    if (command_argument_count() == 1) then
        call get_command_argument(1, buffer)
        read (buffer, '(I5)') n
    else
        n = default_n
    end if
else
    call MPI_Bcast(n, 1, MPI_INTEGER, 0, MPI_COMM_WORLD, ierr)
end if

! create and register types
call create_types(row_type, col_type, n)

! create and initialize local arrays for temperature and old temperature
call allocate_matrix(temp, n)
call init_matrix(temp)
call allocate_matrix(new_temp, n)

! allow diffusion until changes are smaller than tolerance, or the maximum
! number of iterations is exceeded
delta = 0.0_dp
do iter_nr = 1, nr_iters
    if (mod(iter_nr, 2) == 0) then
        call halo_exchange(new_temp, cart_comm, row_type, col_type)
        call update_matrix(new_temp, temp, delta)
    else
        call halo_exchange(temp, cart_comm, row_type, col_type)
        call update_matrix(temp, new_temp, delta)
    end if
    if (delta < tol) exit
end do

! compute average temperature
call compute_avg(temp, avg_temp, cart_comm)

! process 0 will report
if (comm_rank == 0) then
    print '(I0, A, A, E15.5, A, E15.5)', iter_nr - 1, ' iterations ', &
        ' with delta = ', delta, ', average temp. = ', avg_temp
end if

! take down MPI
call MPI_Finalize(ierr)

contains

! routine to allocate an nxn matrix
    subroutine allocate_matrix(matrix, n)
        implicit none
        real(kind=dp), dimension(:, :), allocatable, intent(inout) :: matrix
        integer, intent(in) :: n
        allocate(matrix(n, n), stat=ierr)
        if (ierr /= 0) then
            write (error_unit, '(A, I0)') &
                'can not allocate temp in ', comm_rank
            call MPI_Abort(MPI_COMM_WORLD, MEM_ALLOC_ERR, ierr)
        end if
    end subroutine allocate_matrix

! create MPI types for halo exchange
    subroutine create_types(row_type, col_type, n)
        implicit none
        integer, intent(inout) :: row_type, col_type
        integer, intent(in) :: n
        integer :: ierr
        call MPI_Type_vector(n, 1, n, MPI_DOUBLE_PRECISION, row_type, ierr)
        call MPI_Type_commit(row_type, ierr)
        call MPI_type_contiguous(n, MPI_DOUBLE_PRECISION, col_type, ierr)
        call MPI_Type_commit(col_type, ierr)
     end subroutine create_types

! initialize a matrix, mostly to zero, some elements randomly to a
! non-zero value
    subroutine init_matrix(matrix)
        implicit none
        real(kind=dp), dimension(:, :), intent(inout) :: matrix
        real(kind=dp), parameter :: min_val = 0.0_dp, max_val = 1.0_dp, &
                                    prob = 0.1_dp
        integer :: i, j
        real(kind=dp) :: r
        do j = 1, size(matrix, 2)
            do i = 1, size(matrix, 1)
                call random_number(r)
                if (r < prob) then
                    matrix(i, j) = max_val
                else
                    matrix(i, j) = min_val
                end if
            end do
        end do
    end subroutine init_matrix

! perform a single update step for the diffusion
    subroutine update_matrix(matrix, new_matrix, delta)
        implicit none
        real(kind=dp), dimension(:, :), intent(in) :: matrix
        real(kind=dp), dimension(:, :), intent(inout) :: new_matrix
        real(kind=dp), intent(out) :: delta
        real(kind=dp), parameter :: delta_t = 0.01_dp
        integer :: i, j
        delta = 0.0_dp
        do j = 2, size(matrix, 2) - 1
            do i = 2, size(matrix, 1) - 1
                new_matrix(i, j) = 0.25_dp*(matrix(i - 1, j) + &
                                            matrix(i + 1, j) + &
                                            matrix(i, j - 1) + &
                                            matrix(i, j + 1))
                delta = max(delta, abs(new_matrix(i, j) - matrix(i, j)))
            end do
        end do
    end subroutine update_matrix

    subroutine halo_exchange(matrix, comm, row_type, col_type)
        implicit none
        real(kind=dp), dimension(:, :), intent(inout) :: matrix
        integer, intent(in) :: comm, row_type, col_type
        integer, parameter :: tag = 17
        integer :: up, right, down, left, comm_rank, ierr, nr_rows, nr_cols
        nr_rows = size(matrix, 1)
        nr_cols = size(matrix, 2)
        call MPI_Comm_rank(comm, comm_rank, ierr)
        call MPI_Cart_shift(comm, 0, 1, left, right, ierr)
        call MPI_Cart_shift(comm, 1, 1, up, down, ierr)
        call MPI_Sendrecv(matrix(2, 1), 1, row_type, up, tag, &
                          matrix(1, 1), 1, row_type, down, tag, &
                          comm, MPI_STATUS_IGNORE, ierr)
        call MPI_Sendrecv(matrix(nr_rows - 1, 1), 1, row_type, down, tag, &
                          matrix(nr_rows, 1), 1, row_type, up, tag, &
                          comm, MPI_STATUS_IGNORE, ierr)
        call MPI_Sendrecv(matrix(1, 2), 1, col_type, left, tag, &
                          matrix(1, 1), 1, col_type, right, tag, &
                          comm, MPI_STATUS_IGNORE, ierr)
        call MPI_Sendrecv(matrix(1, nr_cols - 1), 1, col_type, right, tag, &
                          matrix(1, nr_cols), 1, col_type, left, tag, &
                          comm, MPI_STATUS_IGNORE, ierr)
    end subroutine halo_exchange

! compute the local average, and compute global average in rank 0
    subroutine compute_avg(matrix, avg, comm)
        implicit none
        real(kind=dp), dimension(:, :), intent(in) :: matrix
        real(kind=dp), intent(out) :: avg
        integer, intent(in) :: comm
        real(kind=dp) :: local_avg
        integer :: comm_size, ierr
        call MPI_Comm_size(comm, comm_size, ierr)
        local_avg = sum(matrix)/size(matrix)
        call MPI_Reduce(local_avg, avg, 1, MPI_DOUBLE_PRECISION, MPI_SUM, &
                        0, comm, ierr)
        avg = avg/comm_size
    end subroutine compute_avg

end program diffusion
