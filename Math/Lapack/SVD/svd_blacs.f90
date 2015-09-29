program svd_blacs
    use mpi
    implicit none
    integer, parameter :: nr_matrix_rows = 17, nr_matrix_cols = 13, &
                          row_block_size = 3, col_block_size = 4
    integer :: proc_nr, nr_procs, context, ierr, rank, size, &
               nr_proc_rows, nr_proc_cols, proc_row, proc_col, &
               nr_local_rows, nr_local_cols, row_offset, col_offset, &
               row_start, row_stride, col_start, col_stride
    integer, dimension(2) :: grid_dims
    character, parameter :: orientation = 'R'
    integer :: numroc
    integer :: i

    call blacs_pinfo(proc_nr, nr_procs)
    call blacs_get(0, 0, context)
    call mpi_comm_rank(MPI_COMM_WORLD, rank, ierr)
    call mpi_comm_size(MPI_COMM_WORLD, size, ierr)
    if (rank == 0) then
        print "(2(A, I0))", "matrix ", nr_matrix_rows, " x ", nr_matrix_cols
        print "(2(A, I0))", "blocking ", &
                            row_block_size, " x ", col_block_size
    end if
    grid_dims = 0
    call mpi_dims_create(nr_procs, 2, grid_dims, ierr)
    call blacs_gridinit(context, orientation, grid_dims(1), grid_dims(2))
    call blacs_gridinfo(context, nr_proc_rows, nr_proc_cols, &              
                        proc_row, proc_col)                           
    nr_local_rows = numroc(nr_matrix_rows, row_block_size, proc_row, 0, &
                           nr_proc_rows)
    nr_local_cols = numroc(nr_matrix_cols, col_block_size, proc_col, 0, &
                           nr_proc_cols)
    print "(5(A, I0))", "rank ", rank, &
                        ", proc row ", proc_row, &
                        ", proc col ", proc_col, &
                        ", local rows ", nr_local_rows, &
                        ", local cols ", nr_local_cols
    do i = 0, size
        if (rank == i) then
            print "(A, I0)", "rank ", rank
            row_start = proc_row*row_block_size
            row_stride = nr_proc_rows*row_block_size
            col_start = proc_col*col_block_size
            col_stride = nr_proc_cols*col_block_size
            do row_offset = row_start, nr_matrix_rows, row_stride
                do col_offset = col_start, nr_matrix_cols, col_stride
                    print "(I0, A, I0)", row_offset, ", ", col_offset
                end do
            end do
        end if
        call mpi_barrier(MPI_COMM_WORLD, ierr)
    end do
    call blacs_exit(0)

end program svd_blacs
