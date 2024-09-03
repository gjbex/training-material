program one_sided
use, intrinsic :: iso_fortran_env, only : dp => REAL64
use mpi_f08
implicit none
integer, parameter :: nr_buffer_elems = 2
integer :: rank, size, right, left, disp_int
real(kind=dp) :: val
real(kind=dp), asynchronous, dimension(nr_buffer_elems) :: buffer
integer(kind=MPI_ADDRESS_KIND) :: dp_size, lb, disp_aint

type(MPI_Win) :: window

call MPI_Init()
call MPI_Comm_size(MPI_COMM_WORLD, size)
call MPI_Comm_rank(MPI_COMM_WORLD, rank)
val = 1.1_dp*rank
buffer(1) = -1.0_dp
buffer(2) = val + 100.0_dp
if (rank == size - 1) then
    right = 0
else
    right = rank + 1
end if
if (rank == 0) then
    left = size - 1
else
    left = rank - 1
end if
print '(A, F5.1, A, I0, A, I0)', 'will put ', val, ' from ', rank, &
    ' into ', right
print '(I0, A, F5.1, A, I0)', left, ' will take ', buffer(2), ' from ', rank
call MPI_Type_get_extent(MPI_DOUBLE_PRECISION, lb, dp_size)
disp_int = int(dp_size, kind=kind(disp_int))
if (.not. MPI_ASYNC_PROTECTS_NONBLOCKING) &
    call MPI_F_sync_reg(buffer)
call MPI_Win_create(buffer, nr_buffer_elems*dp_size, disp_int, &
                    MPI_INFO_NULL, MPI_COMM_WORLD, window)
call MPI_Win_fence(MPI_MODE_NOPRECEDE, window)
disp_aint = 0
call MPI_Put(val, 1, MPI_DOUBLE_PRECISION, right, &
             disp_aint, 1, MPI_DOUBLE_PRECISION, window)
disp_aint = 1
call MPI_Get(val, 1, MPI_DOUBLE_PRECISION, right, &
             disp_aint, 1, MPI_DOUBLE_PRECISION, window)
call MPI_Win_fence(MPI_MODE_NOSUCCEED, window)
if (.not. MPI_ASYNC_PROTECTS_NONBLOCKING) &
    call MPI_F_sync_reg(buffer)

print '(A, F5.1, A, I0, A, I0)', 'got ', val, ' into ', rank, &
    ' from ', right
print '(F5.1, A, I0, A, I0)', buffer(1), ' was put by ', left, &
    ' into ', rank

call MPI_Win_free(window)

call MPI_Finalize()

end program one_sided
