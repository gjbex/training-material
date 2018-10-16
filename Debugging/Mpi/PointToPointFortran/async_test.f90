program async_test
    use :: mpi_f08
    implicit none
    integer :: my_rank

    call MPI_Init()
    call MPI_Comm_rank(MPI_COMM_WORLD, my_rank)
    if (MPI_ASYNC_PROTECTS_NONBLOCKING) then
        print '("rank ", I0, " protects async")', my_rank
    else
        print '("rank ", I0, " does not protect async")', my_rank
    end if
    call MPI_Finalize()
end program async_test
