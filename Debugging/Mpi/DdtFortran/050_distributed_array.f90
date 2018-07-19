program distributed_array
    use, intrinsic :: iso_fortran_env, only : r8 => REAL64
    use :: mpi
    implicit none
    integer, parameter :: local_rows = 300, local_cols = 400, &
                          nr_dims = 2
    logical, parameter, dimension(nr_dims) :: periodic = [ .false., .false. ]
    logical, parameter :: reorder = .false.
    integer :: proc_rows, proc_cols, row, col, proc_row, proc_col
    integer :: rank, size, ierr, val
    integer, dimension(nr_dims) :: dims = [ 0, 0 ], cart_coords
    real(kind=r8), dimension(local_rows, local_cols) :: data
    real(kind=r8) :: r
    integer :: cart_comm

    call MPI_Init(ierr)
    call MPI_Comm_rank(MPI_COMM_WORLD, rank, ierr)
    call MPI_Comm_size(MPI_COMM_WORLD, size, ierr)
    call MPI_Dims_create(size, nr_dims, dims, ierr)
    proc_rows = dims(1)
    proc_cols = dims(2)
    call MPI_Cart_create(MPI_COMM_WORLD, nr_dims, dims, periodic, &
                         reorder, cart_comm, ierr)
    call MPI_Cart_coords(cart_comm, rank, nr_dims, cart_coords, ierr)
    proc_row = cart_coords(1)
    proc_col = cart_coords(2)
   do row = 1, local_rows
       do col = 1, local_cols
           call random_number(r)
           if (r < 0.999_r8) then
               call random_number(r)
               data(row, col) = r
           else
               call random_number(r)
               data(row, col) = sqrt(-r)
           end if
       end do
   end do
   call MPI_Barrier(MPI_COMM_WORLD, ierr)
   call MPI_Finalize(ierr)
end program distributed_array
