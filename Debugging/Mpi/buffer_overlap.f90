program message_size
use :: mpi
implicit none
integer, parameter :: root = 0
integer, parameter :: buff_size = 5
integer, dimension(buff_size) :: buff
integer :: ierr, rank, i

call MPI_Init(ierr)
call MPI_Comm_rank(MPI_COMM_WORLD, rank, ierr)
do i = 1, buff_size
    buff(i) = i
end do

call MPI_Reduce(buff, buff, buff_size, MPI_INTEGER, MPI_SUM, root, &
                MPI_COMM_WORLD, ierr)

if (rank == root) then
    do i = 1, buff_size
        print '(I15)', buff(i)
    end do
end if

call MPI_Finalize(ierr)

end program message_size
