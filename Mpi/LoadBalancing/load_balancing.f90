program load_balancing
    use :: mpi
    implicit none
    integer :: size, rank, n, ierr, lbound, ubound, i
    character(len=1024) :: buffer

    call MPI_Init(ierr)
    call MPI_Comm_rank(MPI_COMM_WORLD, rank, ierr)
    call MPI_Comm_size(MPI_COMM_WORLD, size, ierr)
    if (rank == 0) then
        if (command_argument_count() >= 1) then
            call get_command_argument(1, buffer)
            read (buffer, '(I10)') n
        else
            n = 1003
        end if
    end if
    call MPI_Bcast(n, 1, MPI_INTEGER, 0, MPI_COMM_WORLD, ierr)

    call compute_bounds(size, rank, n, lbound, ubound)
    do i = 0, size - 1
        if (rank == i) print '(I3, 2I10)', rank, lbound, ubound
        call MPI_Barrier(MPI_COMM_WORLD, ierr)
    end do

    call MPI_Finalize(ierr)

contains

    subroutine compute_bounds(size, rank, n, lbound, ubound)
        implicit none
        integer, intent(in) :: size, rank, n
        integer, intent(out) :: lbound, ubound
        integer :: chunk_size, rest
        chunk_size = n/size
        rest = mod(n, size)
        lbound = min(rank, size - rest)*chunk_size + &
                 max(0, rank - (size - rest))*(chunk_size + 1)
        ubound = lbound + chunk_size
        if (rank >= size - rest) ubound = ubound + 1
        lbound = lbound + 1
    end subroutine compute_bounds

end program load_balancing
