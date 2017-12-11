program scatter_gather
use mpi_f08
use, intrinsic :: iso_fortran_env, only : dp => REAL64, error_unit
implicit none
integer, parameter :: root = 0
integer :: rank, size, i, stat, type_size
type(MPI_Datatype) :: real_type
real(kind=dp), dimension(:), allocatable :: root_buffer
real(kind=dp) :: val_buffer

call MPI_Init()
call MPI_Comm_size(MPI_COMM_WORLD, size)
call MPI_Comm_rank(MPI_COMM_WORLD, rank)

! determine MPI type of real data dynamically
call MPI_Sizeof(val_buffer, type_size)
call MPI_Type_match_size(MPI_TYPECLASS_REAL, type_size, real_type)

! allocate buffer in root, initialize, and scatter
if (rank == root) then
    allocate(root_buffer(size), stat=stat)
    if (stat /= 0) then
        write (error_unit, "(A)") "### error: can not allocate"
    end if
    do i = 1, size
        root_buffer(i) = real(i - 1, kind=dp)
    end do
end if
call MPI_Scatter(root_buffer, 1, real_type, &
                 val_buffer, 1, real_type, &
                 root, MPI_COMM_WORLD)
! print received value and do complicated computation
print "(A, I2, A, F5.1)", "rank ", rank, " received ", val_buffer
val_buffer = val_buffer**2

! gather and root prints results
call MPI_Gather(val_buffer, 1, real_type, &
                root_buffer, 1, real_type, &
                root, MPI_COMM_WORLD)
if (rank == root) then
    print "(A)", "root received:"
    print "(F5.1)", root_buffer
end if
call MPI_Finalize()

end program scatter_gather
