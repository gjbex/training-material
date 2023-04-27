program sparse_sends
use, intrinsic :: iso_fortran_env, only : error_unit, dp => REAL64, sp => REAL32
use mpi_f08
implicit none
integer :: my_rank, my_size, incr, i, msg_buff, n, iter, nr_iters, stat, origin_idx, rank
integer, asynchronous :: nr_recvs
type(MPI_Win) :: window
integer :: disp_unit
integer(kind=MPI_ADDRESS_KIND) :: integer_my_size, lb, recv_buff_my_size, &
                                  target_disp
integer, dimension(:), allocatable :: seed, origin_ranks
integer, parameter :: tag = 17, target_rank = 0
integer, dimension(1) :: target_ranks = [target_rank]
real(kind=sp) :: r, prob
logical :: will_send
type(MPI_Group) :: win_group, origin_group, target_group
type(MPI_Status) :: status

! setup MPI and determine rank & my_size
call MPI_init()
call MPI_Comm_size(MPI_COMM_WORLD, my_size)
call MPI_Comm_rank(MPI_COMM_WORLD, my_rank)

! initalize the array that contains the ranks of the (potential) origin
! ranks
allocate(origin_ranks(my_size - 1), stat=stat)
if (stat /= 0) then
    write (unit=error_unit, fmt='(A)') 'error: can not allocate origin_ranks array'
    stop 1
end if
origin_idx = 1
do rank = 0, my_size - 1
    if (rank /= target_rank) then
        origin_ranks(origin_idx) = rank
        origin_idx = origin_idx + 1
    end if
end do

! seed random number generator, this is a really, really bad method,
! don't do this at home!
call random_seed(size = n)
allocate(seed(n))
if (stat /= 0) then
    write (unit=error_unit, fmt='(A)') 'error: can not allocate seed array'
    stop 1
end if
do i = 1, n
    seed(i) = (my_rank + i)*17 + i*253 + i**2*9193*my_rank**2
end do
call random_seed(put=seed)

! initialize send probabiltiy, on average, prob*(my_size - 1) processes will
! send, as well as the number of iterations
prob = 0.5
nr_iters = 3

! compute the my_size of the receive buffer in bytes, as well as the
! displacement units in bytes.
call MPI_Type_get_extent(MPI_INTEGER, lb, integer_my_size)
recv_buff_my_size = 1*integer_my_size
disp_unit = integer_my_size

! create a window for one-sided communication, nr_recvs acts as the
! receive buffer
call MPI_Win_create(nr_recvs, recv_buff_my_size, disp_unit, MPI_INFO_NULL, &
                    MPI_COMM_WORLD, window)
call MPI_Win_get_group(window, win_group)

! create origin and target groups
call MPI_Group_incl(win_group, size(origin_ranks), origin_ranks, origin_group)
call MPI_Group_incl(win_group, size(target_ranks), target_ranks, target_group)

do iter = 1, nr_iters
    ! start local store epoch
    if (my_rank == target_rank) then
        nr_recvs = 0
    end if


    ! start RMA epoch, only processes intending to send add 1 to nr_recvs
    if (.not. MPI_ASYNC_PROTECTS_NONBLOCKING) &
        call MPI_F_SYNC_REG(nr_recvs)
    if (my_rank == target_rank) then
        call MPI_Win_post(origin_group, 0, window)
        print '(A, I0, A)', 'iteration ', iter, ': win_post done'
    elseif (my_rank /= target_rank) then
        call random_number(r)
        will_send = r < prob 
        call MPI_Win_start(target_group, 0, window)
        if (will_send) then
            print '(A, I0, A, I0)', 'will send: ', my_rank, ' in ', iter
            incr = 1
            target_disp = 0
            call MPI_Accumulate(incr, 1, MPI_INTEGER, target_rank, &
                                target_disp, 1, MPI_INTEGER, &
                                MPI_SUM, window)
        end if
        call MPI_Win_complete(window)
    end if
    if (my_rank == target_rank) then
        print '(A, I0, A)', 'iteration ', iter, ': waiting for completion'
        call MPI_Win_wait(window)
        print '(A, I0, A,I0, A)', 'iteration ', iter, ': ', nr_recvs, ' processes will send'
    end if
    if (.not. MPI_ASYNC_PROTECTS_NONBLOCKING) &
        call MPI_F_SYNC_REG(nr_recvs)

    ! for debugging, print the number of senders
    if (my_rank == target_rank) then
        print '(A, I0, A, I0)', 'expecting ', nr_recvs, ' in ', iter
    end if

    ! the target will receive nr_recvs messages, each process willing
    ! to send sends 1
    if (my_rank == target_rank) then
        do i = 1, nr_recvs
            call MPI_Recv(msg_buff, 1, MPI_INTEGER, MPI_ANY_SOURCE, tag, &
                          MPI_COMM_WORLD, status)
            print '(A, I0, A, I0)', 'received from ', status%MPI_SOURCE, &
                                        ' in ', iter
        end do
    else
        if (will_send) then
            call MPI_Send(my_rank, 1, MPI_INTEGER, target_rank, tag, &
                          MPI_COMM_WORLD)
        end if
    end if
end do

! free window and groups
call MPI_Group_free(origin_group)
call MPI_Group_free(target_group)
call MPI_Group_free(win_group)
call MPI_Win_free(window)

! deallocate arrays
deallocate(origin_ranks)
deallocate(seed)

! finalize MPI
call MPI_Finalize()

end program sparse_sends
