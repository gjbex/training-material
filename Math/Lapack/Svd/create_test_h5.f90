program create_h5
use hdf5
use, intrinsic :: iso_fortran_env, only : dp => REAL64, error_unit
use utils_mod, only : get_file_name
use matrix_mod, only : print_matrix
implicit none
logical, parameter :: verbose = .false.
character(len=1024) :: file_name
character(len=20), parameter :: matrix_dset_name = "matrix"
integer(hid_t) :: file_id, matrix_dset_id, dset_prop_id, &
                  matrix_mspace_id, matrix_fspace_id
integer, parameter :: matrix_rank = 2
integer(hsize_t), dimension(matrix_rank) :: matrix_dim, chunk_dim, offset
integer :: error
integer :: nr_rows, nr_cols, nr_chunk_rows, nr_chunks, chunk_nr
real(kind=dp), allocatable, dimension(:, :) :: matrix_chunk

! get file name from command line
call get_file_name(file_name)

! get matrix dimensions from command line
call get_dimensions(nr_rows, nr_cols)

! set matrix dimensions
matrix_dim(1) = nr_rows
matrix_dim(2) = nr_cols

! set chunk dimensions and allocate
nr_chunk_rows = nr_rows
chunk_dim(1) = nr_chunk_rows
chunk_dim(2) = nr_cols
allocate(matrix_chunk(nr_chunk_rows, nr_cols), stat=error)
if (error /= 0) then
    write (unit=error_unit, fmt="(A)") "matrix chunk can not be allocated"
    stop
end if
nr_chunks  = nr_rows/nr_chunk_rows

! initialize Fortran interface
call h5open_f(error)

! open the HDF5 file, overwriting it if it alread exists
call h5fcreate_f(file_name, H5F_ACC_TRUNC_F, file_id, error)
if (error /= 0) then
    write (unit=error_unit, fmt="(2A)") "# error opening file ", &
                                        file_name
    stop
end if

! create the matrix file dataspace, specify data rank and dimentions
call h5screate_simple_f(matrix_rank, matrix_dim, matrix_fspace_id, error)

! create the chunk memory dataspace
call h5screate_simple_f(matrix_rank, chunk_dim, matrix_mspace_id, error)

! create the matrix dataset in the root, using the data type and
! the dataspace ID, use chunking for performance reasons
call h5pcreate_f(H5P_DATASET_CREATE_F, dset_prop_id, error)
call h5pset_chunk_f(dset_prop_id, matrix_rank, chunk_dim, error)
call h5dcreate_f(file_id, matrix_dset_name, H5T_NATIVE_DOUBLE, &
                 matrix_fspace_id, matrix_dset_id, error, dset_prop_id)
call h5pclose_f(dset_prop_id, error)

! write matrix data, chunk by chunk, selecting the appropriate hyperslab
do chunk_nr = 1, nr_chunks
    call compute_data(matrix_chunk)
    if (verbose) then
        print "(A, I0)", "chunk ", chunk_nr
        call print_matrix(matrix_chunk)
    end if
    offset(1) = (chunk_nr - 1)*nr_chunk_rows
    offset(2) = 0
    call h5sselect_hyperslab_f(matrix_fspace_id, H5S_SELECT_SET_F, &
                               offset, chunk_dim, error)
    call h5dwrite_f(matrix_dset_id, H5T_NATIVE_DOUBLE, matrix_chunk, &
                    chunk_dim, error, mem_space_id=matrix_mspace_id, &
                    file_space_id=matrix_fspace_id)
end do

! close matrix data set
call h5dclose_f(matrix_dset_id, error)

! close matrix data spaces (file and memory)
call h5sclose_f(matrix_mspace_id, error)
call h5sclose_f(matrix_fspace_id, error)

! close HDF5 file
call h5fclose_f(file_id, error)

! finalize Fortran HDF5 interface
call h5close_f(error)

contains

    subroutine get_dimensions(nr_rows, nr_cols)
        implicit none
        integer, intent(out) :: nr_rows, nr_cols
        character(len=1024) :: argv
        if (command_argument_count() < 3) then
            write (unit=error_unit, fmt="(A)") &
                "# warning: using default dimensions"
            nr_rows = 5
            nr_cols = 6
        else
            call get_command_argument(2, argv)
            read (argv, *) nr_rows
            call get_command_argument(3, argv)
            read (argv, *) nr_cols
        end if
    end subroutine get_dimensions

    subroutine get_chunk_size(nr_chunk_rows)
        implicit none
        integer, intent(out) :: nr_chunk_rows
        character(len=1024) :: argv
        if (command_argument_count() < 4) then
            write (unit=error_unit, fmt="(A)") &
                "# warning: using default chunk size"
            nr_chunk_rows = 1
        else
            call get_command_argument(4, argv)
            read (argv, *) nr_chunk_rows
        end if
    end subroutine get_chunk_size

    subroutine compute_data(chunk)
        implicit none
        real(kind=dp), dimension(:, :), intent(inout) :: chunk
        integer i, j
        real(kind=dp) :: value
        value = 0.0_dp
        do i = 1, size(chunk, 1)
            do j = 1, size(chunk, 2)
                value = value + 1.0_dp
                chunk(i, j) = value
            end do
        end do
    end subroutine compute_data

end program create_h5
