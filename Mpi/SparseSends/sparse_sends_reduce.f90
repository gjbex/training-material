program sparse_sends
use, intrinsic :: iso_fortran_env, only : dp => REAL64, sp => REAL32
use mpi_f08
implicit none
integer :: rank, size, i, msg_buff, n, iter, nr_iters
integer, dimension(:), allocatable :: seed                                  
integer, parameter :: tag = 17, target_rank = 0
real(kind=sp) :: r, prob
integer :: will_send, msg_nr, nr_msgs
type(MPI_Status) :: status

! setup MPI and determine rank & size
call MPI_init()
call MPI_Comm_size(MPI_COMM_WORLD, size)
call MPI_Comm_rank(MPI_COMM_WORLD, rank)

! seed random number generator, this is a really, really bad method,
! don't do this at home!
call random_seed(size = n)
allocate(seed(n))
do i = 1, n
    seed(i) = (rank + i)*17 + i*253 + i**2*9193*rank**2
end do
call random_seed(put=seed)

! initialize send probabiltiy, on average, prob*(size - 1) processes will
! send, as well as the number of iterations
prob = 0.5
nr_iters = 3

do iter = 1, nr_iters
    ! if necessary, send, proceed to barrier
    will_send = 0
    if (rank /= target_rank) then
        call random_number(r)
        if (r < prob) then
            print '(A, I0, A, I0)', 'will send: ', rank, ' in ', iter
            will_send = 1
            call MPI_Reduce(will_send, nr_msgs, 1, MPI_INTEGER, MPI_SUM, &
                            target_rank, MPI_COMM_WORLD)
            call MPI_Send(rank, 1, MPI_INTEGER, target_rank, tag, &
                          MPI_COMM_WORLD)
        else
            call MPI_Reduce(will_send, nr_msgs, 1, MPI_INTEGER, MPI_SUM, &
                            target_rank, MPI_COMM_WORLD)
        end if
    else
        call MPI_Reduce(will_send, nr_msgs, 1, MPI_INTEGER, MPI_SUM, &
                        target_rank, MPI_COMM_WORLD)
    end if

    ! the target will receive messages when detected with a probe, if not,
    ! and all other processes are at the barrier, it is done receiving
    ! all other processes simply wait at the barrier
    if (rank == target_rank) then
        do msg_nr = 1, nr_msgs
            call MPI_Recv(msg_buff, 1, MPI_INTEGER, MPI_ANY_SOURCE, &
                      tag, MPI_COMM_WORLD, status)
            print '(A, I0, A, I0)', 'received from ', &
                status%MPI_SOURCE, ' in ', iter
        end do
    end if
    call MPI_Barrier(MPI_COMM_WORLD)
end do

! finalize MPI
call MPI_Finalize()

end program sparse_sends
