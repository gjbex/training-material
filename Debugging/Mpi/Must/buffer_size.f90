program message_size
use :: mpi
implicit none
integer, parameter :: root = 0
integer, parameter :: buff_size = 5
integer, dimension(buff_size + 1) :: buff, recv_buff
integer :: ierr, rank, i

call MPI_Init(ierr)
call MPI_Comm_rank(MPI_COMM_WORLD, rank, ierr)
if (rank == root) then
    do i = 1, buff_size
        buff(i) = i
    end do
end if

if (rank == 1) then
    call MPI_Bcast(buff, buff_size + 1, MPI_INTEGER, root, &
                   MPI_COMM_WORLD, ierr)
else
    call MPI_Bcast(buff, buff_size, MPI_INTEGER, root, &
                   MPI_COMM_WORLD, ierr)
end if

do i = 1, buff_size
    buff(i) = buff(i) + rank
end do

if (rank == 1) then
    call MPI_Reduce(buff, recv_buff, buff_size - 1, MPI_INTEGER, MPI_SUM, &
                    root, MPI_COMM_WORLD, ierr)
else
    call MPI_Reduce(buff, recv_buff, buff_size, MPI_INTEGER, MPI_SUM, &
                    root, MPI_COMM_WORLD, ierr)
end if

if (rank == root) then
    do i = 1, buff_size
        print '(I15)', recv_buff(i)
    end do
end if

call MPI_Finalize(ierr)

end program message_size
