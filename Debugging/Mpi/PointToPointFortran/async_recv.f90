program async_send
    use, intrinsic :: iso_fortran_env, only : error_unit
    use :: mpi_f08
    implicit none
    integer, parameter :: tag = 17
    integer :: my_rank, my_size, partner, sbuff
    integer, asynchronous :: rbuff
    type(MPI_Request) :: request

    call MPI_Init()
    call MPI_Comm_size(MPI_COMM_WORLD, my_size)
    ! it doesn't make sense to run this application with 1 process
    ! only
    if (my_size < 2) then
        write (unit=error_unit, fmt='(A)') &
            '### error: must run with at least two processes'
        call MPI_Abort(MPI_COMM_WORLD, 1)
    end if
    call MPI_Comm_rank(MPI_COMM_WORLD, my_rank)
    sbuff = my_rank
    partner = mod(my_rank + 1, 2)
    print '("rank ", I0, " partners with ", I0)', my_rank, partner
    call MPI_Irecv(rbuff, 1, MPI_INTEGER, partner, tag, &
                   MPI_COMM_WORLD, request)
    call MPI_Send(sbuff, 1, MPI_INTEGER, partner, tag, &
                  MPI_COMM_WORLD)
    if (.not. MPI_ASYNC_PROTECTS_NONBLOCKING) &
        call MPI_F_sync_reg(rbuff)
    call MPI_Wait(request, MPI_STATUS_IGNORE)
    print '("rank ", I0, " received ", I0)', my_rank, rbuff
    call MPI_Finalize()
end program async_send
