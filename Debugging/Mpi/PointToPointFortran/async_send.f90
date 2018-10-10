program async_send
    use, intrinsic :: iso_fortran_env, only : error_unit
    use :: mpi_f08
    implicit none
    integer, parameter :: tag = 17
    integer :: my_rank, my_size, partner, rbuff
    integer, asynchronous :: sbuff
    type(MPI_Request) :: request

    call MPI_Init()
    call MPI_Comm_size(MPI_COMM_WORLD, my_size)
    if (my_size /= 2) then
        write (unit=error_unit, fmt='(A)') &
            '### error: must run with at two processes'
        call MPI_Abort(MPI_COMM_WORLD, 1)
    end if
    call MPI_Comm_rank(MPI_COMM_WORLD, my_rank)
    sbuff = my_rank
    partner = mod(my_rank + 1, 2)
    print '("rank ", I0, " partners with ", I0)', my_rank, partner
    call MPI_Isend(sbuff, 1, MPI_INTEGER, partner, tag, &
                   MPI_COMM_WORLD, request)
    call MPI_Recv(rbuff, 1, MPI_INTEGER, partner, tag, &
                  MPI_COMM_WORLD, MPI_STATUS_IGNORE)
    ! not strictly necessary since we won't reuse sbuff
    if (.not. MPI_ASYNC_PROTECTS_NONBLOCKING) &
        call MPI_F_sync_reg(sbuff)
    call MPI_Wait(request, MPI_STATUS_IGNORE)
    print '("rank ", I0, " received ", I0)', my_rank, rbuff
    call MPI_Finalize()
end program async_send
