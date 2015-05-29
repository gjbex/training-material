program sendrecv
    use, intrinsic :: iso_fortran_env, only : dp => REAL64
    use :: mpi
    implicit none
    integer, parameter :: ndims = 1
    integer, dimension(ndims) :: dims
    logical, dimension(ndims) :: periods = [ .true. ]
    logical ,parameter :: reorder = .true.
    integer :: size, rank, ierr, tag = 11, left, right, comm_cart
    real(kind=dp) :: send_msg, recv_msg

    call MPI_Init(ierr)
    call MPI_Comm_size(MPI_COMM_WORLD, size, ierr)
    dims(1) = size
    call MPI_Cart_create(MPI_COMM_WORLD, ndims, dims, periods, reorder, &
                         comm_cart, ierr)
    call MPI_Comm_rank(comm_cart, rank, ierr)
    call MPI_Cart_shift(comm_cart, 0, 1, left, right, ierr)
    send_msg = rank*1.1_dp
    call MPI_Sendrecv(send_msg, 1, MPI_DOUBLE_PRECISION, left, tag, &
                      recv_msg, 1, MPI_DOUBLE_PRECISION, right, tag, &
                      comm_cart, MPI_STATUS_IGNORE, ierr)
    print '(I0, A, F10.2, A, I0)', &
            rank, ' received ', recv_msg, ' from ', right
    call MPI_Sendrecv(send_msg, 1, MPI_DOUBLE_PRECISION, right, tag, &
                      recv_msg, 1, MPI_DOUBLE_PRECISION, left, tag, &
                      comm_cart, MPI_STATUS_IGNORE, ierr)
    print '(I0, A, F10.2, A, I0)', &
            rank, ' received ', recv_msg, ' from ', left
    call MPI_Finalize(ierr)

end program sendrecv
