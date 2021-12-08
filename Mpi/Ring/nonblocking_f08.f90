program nonblocking
    use, intrinsic :: iso_fortran_env, only : dp => REAL64
    use :: mpi_f08
    implicit none
    integer :: size, rank, tag = 11, left, right
    type(MPI_Request) :: request
    type(MPI_Status)  :: status
    real(kind=dp), asynchronous :: send_msg
    real(kind=dp) :: recv_msg

    call MPI_Init()
    call MPI_Comm_rank(MPI_COMM_WORLD, rank)
    call MPI_Comm_size(MPI_COMM_WORLD, size)
    call neighbours(rank, size, left, right)
    send_msg = rank*1.1_dp
    call MPI_ISend(send_msg, 1, MPI_DOUBLE_PRECISION, right, tag, &
                   MPI_COMM_WORLD, request)
    call MPI_Recv(recv_msg, 1, MPI_DOUBLE_PRECISION, left, tag, &
                  MPI_COMM_WORLD, status)
    print '(I0, A, F10.2)', rank, ' received ', recv_msg
    call MPI_Wait(request, MPI_STATUS_IGNORE)
    ! not strictly necessary in this case since we won't use
    ! send_msg, but just to make the point
    if (.not. MPI_ASYNC_PROTECTS_NONBLOCKING) &
        call MPI_F_sync_reg(send_msg)
    call MPI_Finalize()

contains

    subroutine neighbours(rank, size,  left, right)
        implicit none
        integer, intent(in) :: rank, size
        integer, intent(out) :: left, right
        if (rank == 0) then
            left = size - 1
        else
            left = rank - 1
        end if
        if (rank == size - 1) then
            right = 0
        else
            right = rank + 1
        end if
    end subroutine neighbours

end program nonblocking
