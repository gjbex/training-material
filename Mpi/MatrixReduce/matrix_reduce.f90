program matrix_reduce
use, intrinsic :: iso_fortran_env, only : output_unit, error_unit, &
                                          dp => REAL64
use :: mpi
implicit none
integer, parameter :: root = 0
integer :: rank, size, istat, ierr
integer :: nr_rows, nr_cols, nr_iters, iter, i, j
character(len=15) :: argv
real(kind=dp), allocatable, dimension(:, :) :: matrix, total_matrix
real(kind=dp) :: r, total

call MPI_Init(ierr)
call MPI_Comm_rank(MPI_COMM_WORLD, rank, ierr)
call MPI_Comm_size(MPI_COMM_WORLD, size, ierr)

! get command line arguments, and broadcast them to all
if (rank == root) then
    nr_rows = 5
    if (command_argument_count() >= 1) then
        call get_command_argument(1, argv)
        read (argv, '(I10)') nr_rows
    end if
    if (command_argument_count() >= 2) then
        call get_command_argument(2, argv)
        read (argv, '(I10)') nr_cols
    else
        nr_cols = nr_rows
    end if
    if (command_argument_count() >= 3) then
        call get_command_argument(3, argv)
        read (argv, '(I10)') nr_iters
    else
        nr_iters = 1
    end if
    write (unit=output_unit, fmt='(3(A, I10, /))') &
        'nr. rows: ', nr_rows, &
        'nr. columns: ', nr_cols, &
        'nr. iterations: ', nr_iters
end if
call MPI_Bcast(nr_rows, 1, MPI_INTEGER, root, MPI_COMM_WORLD, ierr)
call MPI_Bcast(nr_cols, 1, MPI_INTEGER, root, MPI_COMM_WORLD, ierr)
call MPI_Bcast(nr_iters, 1, MPI_INTEGER, root, MPI_COMM_WORLD, ierr)

! allocate matrix for each process
allocate(matrix(nr_rows, nr_cols), stat=istat)
if (istat /= 0) then
    write (unit=error_unit, fmt='(A)') 'can not allocate matrix'
    call MPI_Abort(MPI_COMM_WORLD, 1, ierr)
end if

! allocate and initialize matrix for the root process
if (rank == root) then
    allocate(total_matrix(nr_rows, nr_cols), stat=istat)
    if (istat /= 0) then
        write (unit=error_unit, fmt='(A)') 'can not allocate total_matrix'
        call MPI_Abort(MPI_COMM_WORLD, 1, ierr)
    end if
end if

do iter = 1, nr_iters
    call random_number(r)
    do j = 1, nr_cols
        do i = 1, nr_rows
            matrix(i, j) = 2*r + i + rank*(j - 1) + rank*size
        end do
    end do

    call MPI_Reduce(matrix, total_matrix, &
                    nr_rows*nr_cols, MPI_DOUBLE_PRECISION, &
                    MPI_SUM, root, MPI_COMM_WORLD, ierr)
    if (rank == root) then
        total = sum(total_matrix)
        write(unit=output_unit, fmt='(A, I5, F8.1)') &
            'iteration', iter, total
    end if
end do

if (rank == root .and. nr_rows < 20 .and. nr_cols < 20) then
    do i = 1, nr_rows
        write (unit=output_unit, fmt='(*(F8.1))') total_matrix(i, :)
    end do
end if

call MPI_Finalize(ierr)

end program matrix_reduce
