program message_size
use :: mpi
implicit none
integer, parameter :: send_buff_size = 6
integer, parameter :: recv_buff_size = 5
integer, dimension(send_buff_size) :: send_buff
integer, dimension(recv_buff_size) :: recv_buff
integer :: ierr, rank, size, i
integer, parameter :: tag = 17

call MPI_Init(ierr)
call MPI_Comm_rank(MPI_COMM_WORLD, rank, ierr)
call MPI_Comm_size(MPI_COMM_WORLD, size, ierr)
if (rank == 0) then
    do i = 1, send_buff_size
        send_buff(i) = i
    end do
    call MPI_Ssend(send_buff, send_buff_size, MPI_INTEGER, 1, tag, &
                   MPI_COMM_WORLD, ierr)
else if (rank == 1) then
    call MPI_Recv(recv_buff, recv_buff_size, MPI_INTEGER, 0, tag, &
                  MPI_COMM_WORLD, MPI_STATUS_IGNORE, ierr)
    do i = 1, recv_buff_size
        print '(I3)', recv_buff(i)
    end do
end if

call MPI_Finalize(ierr)

end program message_size
