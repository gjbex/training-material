program torus
    use, intrinsic :: iso_fortran_env, only : dp => REAL64
    use :: mpi
    implicit none
    integer, parameter :: ndims = 2
    integer, dimension(ndims) :: dims = [ 0, 0 ], coords
    logical, dimension(ndims) :: periods = [ .true., .true. ]
    logical ,parameter :: reorder = .true.
    integer, dimension(:, :), allocatable :: topology
    integer :: comm_size, rank, ierr, tag = 11, left, right, up, down, &
               comm_cart, i, j, comm_rank
    real(kind=dp) :: send_msg, recv_msg
    character(len=128) :: row_fmt

    call MPI_Init(ierr)
    call MPI_Comm_size(MPI_COMM_WORLD, comm_size, ierr)
    call MPI_Dims_create(comm_size, ndims, dims, ierr)
    call MPI_Cart_create(MPI_COMM_WORLD, ndims, dims, periods, reorder, &
                         comm_cart, ierr)
    call MPI_Comm_rank(comm_cart, rank, ierr)
    call MPI_Cart_coords(comm_cart, rank, ndims, coords, ierr)
    print "(I3, ' -> (', I2, ', ', I2, ')')", rank, coords(1), coords(2)
    call MPI_Barrier(comm_cart, ierr)
    if (rank == 0) then
        allocate(topology(dims(1), dims(2)))
        do i = 0, dims(1) - 1
            do j = 0, dims(2) - 1
                call MPI_Cart_rank(comm_cart, [i, j], comm_rank, ierr)
                topology(i + 1, j + 1) = comm_rank
            end do
        end do
        write (row_fmt, "('(', I0, 'I4)')") dims(2)
        do i = 1, size(topology, 1)
            print row_fmt, topology(i, :)
        end do
        deallocate(topology)
    end if
    call MPI_Barrier(comm_cart, ierr)
    call MPI_Cart_shift(comm_cart, 0, 1, up, down, ierr)
    call MPI_Cart_shift(comm_cart, 1, 1, left, right, ierr)
    print "(I4, ' up:', I4, ' right:', I4, ' down:', I4, ' left:', I4)", &
        rank, up, right, down, left
    send_msg = rank*1.1_dp
    call MPI_Sendrecv(send_msg, 1, MPI_DOUBLE_PRECISION, left, tag, &
                      recv_msg, 1, MPI_DOUBLE_PRECISION, right, tag, &
                      comm_cart, MPI_STATUS_IGNORE, ierr)
    print '(I0, A, F10.2, A, I0)', &
            rank, ' received from right ', recv_msg, ' from ', right
    call MPI_Sendrecv(send_msg, 1, MPI_DOUBLE_PRECISION, right, tag, &
                      recv_msg, 1, MPI_DOUBLE_PRECISION, left, tag, &
                      comm_cart, MPI_STATUS_IGNORE, ierr)
    print '(I0, A, F10.2, A, I0)', &
            rank, ' received from left ', recv_msg, ' from ', left
    call MPI_Sendrecv(send_msg, 1, MPI_DOUBLE_PRECISION, up, tag, &
                      recv_msg, 1, MPI_DOUBLE_PRECISION, down, tag, &
                      comm_cart, MPI_STATUS_IGNORE, ierr)
    print '(I0, A, F10.2, A, I0)', &
            rank, ' received from down ', recv_msg, ' from ', down
    call MPI_Sendrecv(send_msg, 1, MPI_DOUBLE_PRECISION, down, tag, &
                      recv_msg, 1, MPI_DOUBLE_PRECISION, up, tag, &
                      comm_cart, MPI_STATUS_IGNORE, ierr)
    print '(I0, A, F10.2, A, I0)', &
            rank, ' received from up ', recv_msg, ' from ', up
    call MPI_Finalize(ierr)

end program torus
