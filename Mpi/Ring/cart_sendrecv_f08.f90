program sendrecv
    use, intrinsic :: iso_fortran_env, only : dp => REAL64
    use :: mpi_f08
    implicit none
    integer, parameter :: ndims = 1
    integer, dimension(ndims) :: dims
    logical, dimension(ndims) :: periods = [ .true. ]
    logical ,parameter :: reorder = .true.
    integer :: size, rank, tag = 11, left, right
    type(MPI_Comm) :: comm_cart
    real(kind=dp) :: send_msg, recv_msg

    call MPI_Init()
    call MPI_Comm_size(MPI_COMM_WORLD, size)
    dims(1) = size
    call MPI_Cart_create(MPI_COMM_WORLD, ndims, dims, periods, reorder, &
                         comm_cart)
    call MPI_Comm_rank(comm_cart, rank)
    call MPI_Cart_shift(comm_cart, 0, 1, left, right)
    send_msg = rank*1.1_dp
    call MPI_Sendrecv(send_msg, 1, MPI_DOUBLE_PRECISION, left, tag, &
                      recv_msg, 1, MPI_DOUBLE_PRECISION, right, tag, &
                      comm_cart, MPI_STATUS_IGNORE)
    print '(I0, A, F10.2, A, I0)', &
            rank, ' received ', recv_msg, ' from ', right
    call MPI_Sendrecv(send_msg, 1, MPI_DOUBLE_PRECISION, right, tag, &
                      recv_msg, 1, MPI_DOUBLE_PRECISION, left, tag, &
                      comm_cart, MPI_STATUS_IGNORE)
    print '(I0, A, F10.2, A, I0)', &
            rank, ' received ', recv_msg, ' from ', left
    call MPI_Finalize()

end program sendrecv
