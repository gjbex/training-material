program sparse_sends
use, intrinsic :: iso_fortran_env, only : dp => REAL64, sp => REAL32
use mpi_f08
implicit none
integer :: rank, size, i, msg_buff, n, iter, nr_iters
integer, dimension(:), allocatable :: seed                                  
integer, parameter :: tag = 17, target_rank = 0
real(kind=sp) :: r, prob
logical :: will_send, can_receive, all_is_sent
type(MPI_Status) :: status
type(MPI_Request) :: barrier_request

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
    if (rank /= target_rank) then
        call random_number(r)
        will_send = r < prob 
        if (will_send) then
            print '(A, I0, A, I0)', 'will send: ', rank, ' in ', iter
            call MPI_Ssend(rank, 1, MPI_INTEGER, target_rank, tag, &
                           MPI_COMM_WORLD)
        end if
        call MPI_Ibarrier(MPI_COMM_WORLD, barrier_request)
    end if

    ! the target will receive messages when detected with a probe, if not,
    ! and all other processes are at the barrier, it is done receiving
    ! all other processes simply wait at the barrier
    if (rank == target_rank) then
        call MPI_Ibarrier(MPI_COMM_WORLD, barrier_request)
        do while (.true.)
            can_receive = .false.
            all_is_sent = .false.
            call MPI_Iprobe(MPI_ANY_SOURCE, tag, MPI_COMM_WORLD, &
                            can_receive, MPI_STATUS_IGNORE)
            if (can_receive) then
                call MPI_Recv(msg_buff, 1, MPI_INTEGER, MPI_ANY_SOURCE, &
                              tag, MPI_COMM_WORLD, status)
                print '(A, I0, A, I0)', 'received from ', &
                    status%MPI_SOURCE, ' in ', iter
            else
                call MPI_Test(barrier_request, all_is_sent, &
                              MPI_STATUS_IGNORE)
                if (all_is_sent) then
                    exit
                end if
            end if
        end do
    else
        call MPI_Wait(barrier_request, MPI_STATUS_IGNORE)
    end if
end do

! finalize MPI
call MPI_Finalize()

end program sparse_sends
