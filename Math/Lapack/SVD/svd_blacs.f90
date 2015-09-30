program svd_blacs
    use, intrinsic :: iso_fortran_env, only : dp => REAL64
    use matrix_mod, only : get_matrix_dimensions
    use utils_mod, only : get_file_name, get_dataset_name
    implicit none
    logical :: is_verbose = .true.
    integer, parameter :: nr_matrix_rows = 17, nr_matrix_cols = 13, &
                          row_block_size = 3, col_block_size = 4
    character(len=1024) :: file_name, dataset_name
    integer :: proc_nr, nr_procs, context, ierr, &
               nr_proc_rows, nr_proc_cols, proc_row, proc_col, &
               nr_local_rows, nr_local_cols, row_offset, col_offset, &
               row_start, row_size, row_stride, &
               col_start, col_size, col_stride
    integer, dimension(2) :: matrix_dims
    character, parameter :: orientation = "R"
    integer :: numroc
    real(kind=dp), dimension(:, :), allocatable :: A
    integer :: i

! initialize BLACS (initializes MPI under the hood), and determine
! process info
    call init_blacs(proc_nr, nr_procs, context)

! determine and set grid dimensions and retrieve the resulting topology
! information
    call init_blacs_grid(nr_procs, context, orientation, &
                         nr_proc_rows, nr_proc_cols, &               
                         proc_row, proc_col)                           

! get the file and dataset name
    call get_file_name(file_name)
    call get_dataset_name(dataset_name)

! get matrix dimensions
    call get_matrix_dimensions(file_name, dataset_name, matrix_dims)
    if (is_verbose .and. proc_nr == 0) then
        print "(2(A, I0))", "dimesions ", matrix_dims(1), &
                            " x ", matrix_dims(2)
    end if

! determine size of local storage
    call compute_local_storage_sizes(context, &
                                     nr_matrix_rows, nr_matrix_cols, &
                                     row_block_size, col_block_size, &
                                     nr_local_rows, nr_local_cols)
    if (is_verbose) then
        print "(5(A, I0))", "proc_nr ", proc_nr, &
                            ", proc row ", proc_row, &
                            ", proc col ", proc_col, &
                            ", local rows ", nr_local_rows, &
                            ", local cols ", nr_local_cols
    end if

    row_start = proc_row*row_block_size
    row_stride = nr_proc_rows*row_block_size
    col_start = proc_col*col_block_size
    col_stride = nr_proc_cols*col_block_size
    do row_offset = row_start, nr_matrix_rows, row_stride
        row_size = min(row_block_size, nr_matrix_rows - row_offset)
        do col_offset = col_start, nr_matrix_cols, col_stride
            col_size = min(col_block_size, &
                           nr_matrix_cols - col_offset)
            if (is_verbose) then
                print "(A, I0, A, I0, A, I0, A, I0, A, I0)", &
                    "proc_nr ", proc_nr, ": ", &
                    row_offset, ", ", col_offset, " -> ", &
                    row_size, " x ", col_size
            end if
        end do
    end do

! finalize BLACS (finalizes MPI as well)
    call blacs_exit(0)

contains

    subroutine init_blacs(proc_nr, nr_procs, context)
        implicit none
        integer, intent(out) :: proc_nr, nr_procs, context
        call blacs_pinfo(proc_nr, nr_procs)
        call blacs_get(0, 0, context)
    end subroutine init_blacs

    subroutine init_blacs_grid(nr_procs, context, orientation, &
                              nr_proc_rows, nr_proc_cols, &               
                              proc_row, proc_col)
        use mpi
        implicit none
        integer, intent(in) :: nr_procs, context
        character, intent(in) :: orientation
        integer, intent(out) :: nr_proc_rows, nr_proc_cols, &               
                                proc_row, proc_col
        integer, dimension(2) :: dims
        dims = 0
        call mpi_dims_create(nr_procs, 2, dims, ierr)
        call blacs_gridinit(context, orientation, dims(1), dims(2))
        call blacs_gridinfo(context, nr_proc_rows, nr_proc_cols, &
                            proc_row, proc_col)                           
    end subroutine init_blacs_grid

    subroutine compute_local_storage_sizes(context, &
                                           nr_matrix_rows, nr_matrix_cols, &
                                           row_block_size, col_block_size, &
                                           local_rows, local_cols)
        implicit none
        integer, intent(in) :: context, &
                               nr_matrix_rows, nr_matrix_cols, &
                               row_block_size, col_block_size
        integer, intent(out) :: local_rows, local_cols
        integer :: nr_proc_rows, nr_proc_cols, proc_row, proc_col, numroc
        call blacs_gridinfo(context, nr_proc_rows, nr_proc_cols, &
                            proc_row, proc_col)                           
        local_rows = numroc(nr_matrix_rows, row_block_size, proc_row, 0, &
                            nr_proc_rows)
        local_cols = numroc(nr_matrix_cols, col_block_size, proc_col, 0, &
                           nr_proc_cols)
    end subroutine compute_local_storage_sizes
end program svd_blacs
