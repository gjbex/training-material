program hello_world_f08
    use, intrinsic :: iso_fortran_env, only : dp => REAL64
    use :: mpi_f08
    implicit none
    integer :: size, rank, ierr
    real(kind=dp) :: msg

    call MPI_Init(ierr)
    call MPI_Comm_rank(MPI_COMM_WORLD, rank, ierr)
    call MPI_Comm_size(MPI_COMM_WORLD, size, ierr)
    if (rank == 0) &
        print '(A, I0)', 'hello from ', rank
    print '(I0, A, I0)', rank, ' from ', size
    call MPI_Finalize(ierr)

end program hello_world_f08
