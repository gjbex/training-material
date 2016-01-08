program matrix_reduce
use, intrinsic :: iso_fortran_env, only : output_unit, error_unit, &
                                          dp => REAL64
use :: mpi
implicit none
integer, parameter :: nr_rows = 5, nr_cols = 4
integer, parameter :: root = 0
integer :: rank, size, istat, ierr
integer :: i, j
real(kind=dp), allocatable, dimension(:, :) :: matrix, total_matrix
call MPI_Init(ierr)
call MPI_Comm_rank(MPI_COMM_WORLD, rank, ierr)
call MPI_Comm_size(MPI_COMM_WORLD, size, ierr)

! allocate matrix for each process
allocate(matrix(nr_rows, nr_cols), stat=istat)
if (istat /= 0) then
    write (unit=error_unit, fmt='(A)'), 'can not allocate matrix'
    call MPI_Abort(MPI_COMM_WORLD, 1, ierr)
end if

! allocate and initialize matrix for the root process
if (rank == root) then
    allocate(total_matrix(nr_rows, nr_cols), stat=istat)
    if (istat /= 0) then
        write (unit=error_unit, fmt='(A)'), 'can not allocate total_matrix'
        call MPI_Abort(MPI_COMM_WORLD, 1, ierr)
    end if
end if

do j = 1, nr_cols
    do i = 1, nr_rows
        matrix(i, j) = i + rank*(j - 1) + rank*size
    end do
end do

call MPI_Reduce(matrix, total_matrix, &
                nr_rows*nr_cols, MPI_DOUBLE_PRECISION, &
                MPI_SUM, root, MPI_COMM_WORLD, ierr)

if (rank == root) then
    do i = 1, nr_rows
        write (unit=output_unit, fmt='(*(F8.1))') total_matrix(i, :)
    end do
end if

call MPI_Finalize(ierr)

end program matrix_reduce
