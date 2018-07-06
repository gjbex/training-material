program distributed_array
    use :: mpi
    implicit none
    integer, parameter :: local_rows = 3, local_cols = 4, &
                          nr_dims = 2
    logical, parameter, dimension(nr_dims) :: periodic = [ .false., .false. ]
    logical, parameter :: reorder = .false.
    integer :: proc_rows, proc_cols, row, col, proc_row, proc_col
    integer :: rank, size, ierr, val
    integer, dimension(nr_dims) :: dims = [ 0, 0 ], cart_coords
    integer, dimension(local_rows, local_cols) :: data
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
           val = proc_row*local_rows*local_cols*proc_cols + &
                 (row - 1)*local_cols*proc_cols + &
                 (col - 1) + proc_col*local_cols
           data(row, col) = val
       end do
   end do
   call MPI_Barrier(MPI_COMM_WORLD, ierr)
   call MPI_Finalize(ierr)
end program distributed_array
