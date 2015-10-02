program svd_blacs
    use, intrinsic :: iso_fortran_env, only : dp => REAL64, error_unit
    use hdf5
    use mpi
    use matrix_mod, only : print_matrix
    use utils_mod, only : get_file_name, get_dataset_name, get_block_size
    implicit none
    integer, parameter :: DLEN_ = 9, DTYPE_ = 1, CTXT_ = 2, &
                          M_ = 3, N_ = 4, MB_ = 5, NB_ = 6, &
                          RSRC_ = 7, CSRC_ = 8, LLD_ = 9
    logical :: is_verbose = .true.
    ! Note that for pdgesvd the row and column blocking size must be the
    ! same, hence only a single variable is defined to avoid mistakes
    character(len=1024) :: file_name, dataset_name
    integer :: nr_matrix_rows, nr_matrix_cols, block_size
    integer :: proc_nr, nr_procs, context, ierr, &
               nr_proc_rows, nr_proc_cols, proc_row, proc_col, &
               nr_local_rows, nr_local_cols, row_offset, col_offset, &
               row_start, row_size, row_stride, local_row_start, &
               col_start, col_size, col_stride, local_col_start
    integer(hsize_t), dimension(2) :: offset, chunk_dim, local_offset, &
                                      local_dim
    integer(hid_t) :: file_id, matrix_fspace_id, matrix_dset_id, &
                      matrix_mspace_id
    character, parameter :: orientation = "R"
    integer :: numroc
    real(kind=dp), dimension(:, :), allocatable :: A_local, orig_A_local, &
                                                   U_local, VT_local, &
                                                   Sigma_local, tmp_local
    integer, dimension(DLEN_) :: A_desc, orig_A_desc, U_desc, VT_desc, &
                                 Sigma_desc, tmp_desc
    real(kind=dp), dimension(:), allocatable :: S, work
    real(kind=dp) :: local_error, global_error
    integer :: i, lwork

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
    call get_block_size(block_size)

! prepare for reading HDF5 file
    call init_read(file_name, file_id)

! Open dataset and retrieve dimensions
    call init_dataset(file_id, dataset_name, matrix_dset_id, &
                      matrix_fspace_id, nr_matrix_rows, nr_matrix_cols)
    if (is_verbose .and. proc_nr == 0) then
        print "(2(A, I0))", "dimesions ", nr_matrix_rows, &
                            " x ", nr_matrix_cols
    end if

! determine size of local storage and allocate
    call allocate_matrix(context, nr_matrix_rows, nr_matrix_cols, &
                         block_size, nr_local_rows, nr_local_cols, &
                         A_local, A_desc)
    if (is_verbose) then
        A_local = -1.0_dp
    end if

! create memory space for matrix
    local_dim(1) = nr_local_rows
    local_dim(2) = nr_local_cols
    call h5screate_simple_f(2, local_dim, matrix_mspace_id, ierr)

! for each chunk of the local matrix, create the appropriate hyperslab
! in both the file space and the memory space of the matrix, and read
! it
    row_start = proc_row*block_size
    row_stride = nr_proc_rows*block_size
    col_start = proc_col*block_size
    col_stride = nr_proc_cols*block_size
    local_row_start = 1
    do row_offset = row_start, nr_matrix_rows, row_stride
        local_col_start = 1
        row_size = min(block_size, nr_matrix_rows - row_offset)
        do col_offset = col_start, nr_matrix_cols, col_stride
            col_size = min(block_size, &
                           nr_matrix_cols - col_offset)
            if (is_verbose) then
                print "(A, I0, A, I0, A, I0, A, I0, A, I0)", &
                    "proc_nr ", proc_nr, ": ", &
                    row_offset, ", ", col_offset, " -> ", &
                    row_size, " x ", col_size
            end if
            offset(1) = row_offset
            offset(2) = col_offset
            chunk_dim(1) = row_size
            chunk_dim(2) = col_size
            call h5sselect_hyperslab_f(matrix_fspace_id, H5S_SELECT_SET_F, &
                                       offset, chunk_dim, ierr)
            local_offset(1) = local_row_start - 1
            local_offset(2) = local_col_start - 1
            call h5sselect_hyperslab_f(matrix_mspace_id, H5S_SELECT_SET_F, &
                                       local_offset, chunk_dim, ierr)
            if (is_verbose) then
                print "(A, I0, A, I0, A, I0, A, I0, A, I0)", &
                    "proc_nr ", proc_nr, " local: ", &
                    local_row_start, ", ", local_col_start, " -> ", &
                    chunk_dim(1), " x ", chunk_dim(2)
            end if

            ! read the data
            call h5dread_f(matrix_dset_id, H5T_NATIVE_DOUBLE, &
                           A_local, &
                           chunk_dim, ierr, &
                           mem_space_id=matrix_mspace_id, &
                           file_space_id=matrix_fspace_id)
            local_col_start = local_col_start + block_size
        end do
        local_row_start = local_row_start + block_size
    end do

! close all HDF5 stuff, since reading is done
    call h5sclose_f(matrix_mspace_id, ierr)
    call finalize_dataset(matrix_dset_id, matrix_fspace_id)
    call finalize_read(file_id)

    if (is_verbose) then
        call mpi_barrier(MPI_COMM_WORLD, ierr)
        do i = 0, nr_procs
            if (i == proc_nr) then
                print "(A, I0)", "proc nr ", proc_nr
                call print_matrix(A_local)
            end if
            call mpi_barrier(MPI_COMM_WORLD, ierr)
        end do
    end if

! create orig of original matrix since dgesvd will clobber it    
    call allocate_matrix(context, nr_matrix_rows, nr_matrix_cols, &
                         block_size, nr_local_rows, nr_local_cols, &
                         orig_A_local, orig_A_desc)
    orig_A_local = A_local

! determine size of local storage and allocate U and VT
    call allocate_matrix(context, nr_matrix_rows, nr_matrix_rows, &
                         block_size, nr_local_rows, nr_local_cols, &
                         U_local, U_desc)
    call allocate_matrix(context, nr_matrix_cols, nr_matrix_cols, &
                         block_size, nr_local_rows, nr_local_cols, &
                         VT_local, VT_desc)
! allocate S vector in each process, non-distributed
    allocate(S(min(nr_matrix_rows, nr_matrix_cols)), stat=ierr)
    if (ierr /= 0) then
        write (unit=error_unit, fmt="(A, I0, A, I0)")  &
            "proc_nr ", proc_nr, " can not allocate ", nr_local_rows
        call blacs_exit(0)
    end if

! compute SVD, start by determining the work array size
    lwork = -1
    allocate(work(1))
    call pdgesvd('V', 'V', nr_matrix_rows, nr_matrix_cols, &
                 A_local, 1, 1, A_desc, &
                 S,  U_local, 1, 1, U_desc, VT_local, 1, 1, VT_desc, &
                 work, lwork, ierr)
    if (ierr /= 0) then
        write (unit=error_unit, fmt="(A, I0)") "pdgesvd error code ", ierr
        call blacs_exit(0)
    end if
    lwork = work(1)
    if (is_verbose) then
        print "(A, I0, A, I0)", "proc nr ", proc_nr, " work ", lwork
    end if
    deallocate(work)
    allocate(work(lwork), stat=ierr)
    if (ierr /= 0) then
        write (unit=error_unit, fmt="(A, I0, A, I0)")  &
            "proc_nr ", proc_nr, " can not allocate work ", nr_local_rows
        call blacs_exit(0)
    end if
    call pdgesvd('V', 'V', nr_matrix_rows, nr_matrix_cols, &
                 A_local, 1, 1, A_desc, &
                 S,  U_local, 1, 1, U_desc, VT_local, 1, 1, VT_desc, &
                 work, lwork, ierr)
    if (ierr /= 0) then
        write (unit=error_unit, fmt="(A, I0)") "pdgesvd error code ", ierr
        call blacs_exit(0)
    end if
    deallocate(work)

! to eat some more memory, explicitly construct Sigma, and a temporary
! matrix
    call allocate_matrix(context, nr_matrix_rows, nr_matrix_cols, &
                         block_size, nr_local_rows, nr_local_cols, &
                         Sigma_local, Sigma_desc)
    call init_sigma(S, Sigma_desc, Sigma_local)
    call allocate_matrix(context, nr_matrix_rows, nr_matrix_cols, &
                         block_size, nr_local_rows, nr_local_cols, &
                         tmp_local, tmp_desc)
    call pdgemm('N', 'N', nr_matrix_rows, nr_matrix_cols, nr_matrix_rows, &
                1.0_dp, U_local, 1, 1, U_desc, &
                        Sigma_local, 1, 1, Sigma_desc, &
                0.0_dp, tmp_local, 1, 1, tmp_desc)
    call pdgemm('N', 'N', nr_matrix_rows, nr_matrix_cols, nr_matrix_cols, &
                1.0_dp, tmp_local, 1, 1, tmp_desc, &
                        VT_local, 1, 1, VT_desc, &
                0.0_dp, A_local, 1, 1, A_desc)

    ! compute and print relative error
!    local_error = compute_error(orig_A_local, A)
!    call MPI_Reduce(local_error, global_error, 1, MPI_DOUBLE_PRECISION, &
!                    MPI_SUM, 0, MPI_COMM_WORLD, ierr)
!    if (proc_nr == 0) then
!        print "(A, E10.3)", 'relative error = ', global_error/nr_procs
!    end if
 
! deallocate memory
    deallocate(A_local)
    deallocate(orig_A_local)
    deallocate(U_local)
    deallocate(VT_local)
    deallocate(S)
    deallocate(Sigma_local)
    deallocate(tmp_local)

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
                                           block_size, &
                                           local_rows, local_cols)
        implicit none
        integer, intent(in) :: context, &
                               nr_matrix_rows, nr_matrix_cols, &
                               block_size
        integer, intent(out) :: local_rows, local_cols
        integer :: nr_proc_rows, nr_proc_cols, proc_row, proc_col, numroc
        call blacs_gridinfo(context, nr_proc_rows, nr_proc_cols, &
                            proc_row, proc_col)                           
        local_rows = numroc(nr_matrix_rows, block_size, proc_row, 0, &
                            nr_proc_rows)
        local_cols = numroc(nr_matrix_cols, block_size, proc_col, 0, &
                           nr_proc_cols)
    end subroutine compute_local_storage_sizes
    
    subroutine init_read(file_name, file_id)
        use hdf5
        use, intrinsic :: iso_fortran_env, only : error_unit
        implicit none
        character(len=*), intent(in) :: file_name
        integer(hid_t), intent(out) :: file_id
        integer :: error
        ! initialize Fortran interface
        call h5open_f(error)

        ! open the HDF5 file, overwriting it if it alread exists
        call h5fopen_f(file_name, H5F_ACC_RDONLY_F, file_id, error)
        if (error /= 0) then
            write (unit=error_unit, fmt="(2A)") "# error opening file ", &
                                                file_name
            call blacs_exit(0)
        end if
    end subroutine init_read

    subroutine init_dataset(file_id, matrix_dset_name, matrix_dset_id, &
                            matrix_fspace_id, matrix_rows, matrix_cols)
        use hdf5
        use, intrinsic :: iso_fortran_env, only : error_unit
        implicit none
        integer(hid_t), intent(in) :: file_id
        character(len=*), intent(in) :: matrix_dset_name
        integer(hid_t), intent(out) :: matrix_fspace_id, matrix_dset_id
        integer, intent(out) :: matrix_rows, matrix_cols
        integer(hsize_t), dimension(2) :: matrix_dims, max_matrix_dims
        integer :: error
        ! open the matrix dataset, and get the matrix file dataspace
        call h5dopen_f(file_id, matrix_dset_name, matrix_dset_id, error)
        call h5dget_space_f(matrix_dset_id, matrix_fspace_id, error)

        ! retrieve the dimensions of the matrix, and allocate the matrix
        call h5sget_simple_extent_dims_f(matrix_fspace_id, matrix_dims, &
                                         max_matrix_dims, error)
        matrix_rows = int(matrix_dims(1))
        matrix_cols = int(matrix_dims(2))
    end subroutine init_dataset

    subroutine finalize_dataset(matrix_dset_id, matrix_fspace_id)
        use hdf5
        implicit none
        integer(hid_t), intent(inout) :: matrix_fspace_id, matrix_dset_id
        integer :: error
        ! close dataspaces
        call h5sclose_f(matrix_fspace_id, error)
        ! close the matrix dataset
        call h5dclose_f(matrix_dset_id, error)
    end subroutine finalize_dataset

    subroutine finalize_read(file_id)
        use hdf5
        implicit none
        integer(hid_t), intent(inout) :: file_id
        integer :: error
        ! close HDF5 file
        call h5fclose_f(file_id, error)
        ! finalize Fortran HDF5 interface
        call h5close_f(error)
    end subroutine finalize_read

    subroutine allocate_matrix(context, nr_matrix_rows, nr_matrix_cols, &
                               block_size, nr_local_rows, nr_local_cols, &
                               matrix_local, matrix_desc)
        use, intrinsic :: iso_fortran_env, only : dp => REAL64, error_unit
        implicit none
        integer, intent(in) :: context, nr_matrix_rows, nr_matrix_cols, &
                               block_size 
        integer, intent(out) :: nr_local_rows, nr_local_cols
        real(kind=dp), dimension(:, :), allocatable, &
            intent(inout) :: matrix_local
        integer, dimension(:), intent(inout) :: matrix_desc
        integer :: ierr
        call compute_local_storage_sizes(context, &
                                         nr_matrix_rows, nr_matrix_cols, &
                                         block_size, &
                                         nr_local_rows, nr_local_cols)
        allocate(matrix_local(nr_local_rows, nr_local_cols), stat=ierr)
        if (ierr /= 0) then
            write (unit=error_unit, fmt="(A, I0, A, I0, A, I0)")  &
                "proc_nr ", proc_nr, " can not allocate ", &
                nr_local_rows, " x ", nr_local_cols
            call blacs_exit(0)
        end if
        call descinit(matrix_desc, nr_matrix_rows, nr_matrix_cols, &
                      block_size, block_size, 0, 0, &
                      context, nr_local_rows, ierr)
        if (ierr /= 0) then
            write (unit=error_unit, fmt="(A, I0)") "error in paramter", ierr
            call blacs_exit(0)
        end if
    end subroutine allocate_matrix

    logical function is_mine(block_len, nr_procs, my_proc, g_i)
        implicit none
        integer, intent(in) :: block_len, nr_procs, my_proc, g_i
        integer :: nr_blocks
        nr_blocks = (g_i - 1)/block_len
        is_mine = my_proc == mod(nr_blocks, nr_procs)
    end function is_mine

    subroutine init_sigma(context, block_size, S, Sigma_local)
        use, intrinsic :: iso_fortran_env, only : dp => REAL64
        implicit none
        integer, intent(in) :: context, block_size
        real(kind=dp), dimension(:), intent(in) :: S
        real(kind=dp), dimension(:, :), intent(inout) :: Sigma
        integer :: nr_proc_rows, nr_proc_cols, proc_row, proc_col, i, index
        call blacs_gridinfo(context, nr_proc_rows, nr_proc_cols, &
                            proc_row, proc_col)                           
        Sigma_local = 0.0_dp
        index = 1
        do i = 1, size(S)
            if (is_mine(block_size, nr_proc_rows, proc_row, i) .and. &
                is_mine(block_size, nr_proc_cols, proc_col, i)) then
                Sigma_local(index, index) = S(i)
                index = index + 1
            end if
        end do
    end subroutine init_sigma

end program svd_blacs
