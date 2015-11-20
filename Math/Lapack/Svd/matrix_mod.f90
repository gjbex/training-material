module matrix_mod
implicit none

contains

    subroutine get_matrix_dimensions(file_name, matrix_dset_name, &
                                     dims)
        use hdf5
        use, intrinsic :: iso_fortran_env, only : dp => REAL64, error_unit
        implicit none
        integer, parameter :: matrix_rank = 2
        character(len=*), intent(in) :: file_name, matrix_dset_name
        integer, dimension(matrix_rank) :: dims
        integer(hid_t) :: file_id, matrix_dset_id, dset_prop_id, &
                          matrix_mspace_id, matrix_fspace_id
        integer(hsize_t), dimension(matrix_rank) :: matrix_dims, &
                                                max_matrix_dims
        integer :: error
        call h5open_f(error)

        ! open the HDF5 file, overwriting it if it alread exists
        call h5fopen_f(file_name, H5F_ACC_RDONLY_F, file_id, error)
        if (error /= 0) then
            write (unit=error_unit, fmt="(2A)") "# error opening file ", &
                                                file_name
            stop
        end if

        ! open the matrix dataset, and get the matrix file dataspace
        call h5dopen_f(file_id, matrix_dset_name, matrix_dset_id, error)
        call h5dget_space_f(matrix_dset_id, matrix_fspace_id, error)

        ! retrieve the dimensions of the matrix, and allocate the matrix
        call h5sget_simple_extent_dims_f(matrix_fspace_id, matrix_dims, &
                                         max_matrix_dims, error)
        ! close the matrix dataset
        call h5dclose_f(matrix_dset_id, error)

        ! close HDF5 file
        call h5fclose_f(file_id, error)

        ! finalize Fortran HDF5 interface
        call h5close_f(error)
        dims = int(matrix_dims)
    end subroutine get_matrix_dimensions

    subroutine read_matrix(file_name, matrix_dset_name, matrix)
        use hdf5
        use, intrinsic :: iso_fortran_env, only : dp => REAL64, error_unit
        implicit none
        character(len=*), intent(in) :: file_name, matrix_dset_name
        real(kind=dp), allocatable, dimension(:, :), intent(out) :: matrix
        integer(hid_t) :: file_id, matrix_dset_id, dset_prop_id, &
                          matrix_mspace_id, matrix_fspace_id
        integer, parameter :: matrix_rank = 2
        integer(hsize_t), dimension(matrix_rank) :: matrix_dims, &
                                                    max_matrix_dims, &
                                                    chunk_dims
        integer :: error
        ! initialize Fortran interface
        call h5open_f(error)

        ! open the HDF5 file, overwriting it if it alread exists
        call h5fopen_f(file_name, H5F_ACC_RDONLY_F, file_id, error)
        if (error /= 0) then
            write (unit=error_unit, fmt="(2A)") "# error opening file ", &
                                                file_name
            stop
        end if

        ! open the matrix dataset, and get the matrix file dataspace
        call h5dopen_f(file_id, matrix_dset_name, matrix_dset_id, error)
        call h5dget_space_f(matrix_dset_id, matrix_fspace_id, error)

        ! retrieve the dimensions of the matrix, and allocate the matrix
        call h5sget_simple_extent_dims_f(matrix_fspace_id, matrix_dims, &
                                         max_matrix_dims, error)
        allocate(matrix(matrix_dims(1), matrix_dims(2)), stat=error)
        if (error /= 0) then
            write (unit=error_unit, fmt="(A)") &
                "matrix chunk can not be allocated"
            stop
        end if

        ! create the matrix memory dataspace
        call h5screate_simple_f(matrix_rank, matrix_dims, &
                                matrix_mspace_id, error)

        ! read the data
        call h5dread_f(matrix_dset_id, H5T_NATIVE_DOUBLE, matrix, &
                       matrix_dims, error, mem_space_id=matrix_mspace_id, &
                       file_space_id=matrix_fspace_id)

        ! close dataspaces
        call h5sclose_f(matrix_mspace_id, error)
        call h5sclose_f(matrix_fspace_id, error)

        ! close the matrix dataset
        call h5dclose_f(matrix_dset_id, error)

        ! close HDF5 file
        call h5fclose_f(file_id, error)

        ! finalize Fortran HDF5 interface
        call h5close_f(error)
    end subroutine read_matrix

    subroutine print_matrix(matrix)
        use, intrinsic :: iso_fortran_env, only : dp => REAL64
        implicit none
        real(kind=dp), dimension(:, :), intent(in) :: matrix
        integer i
        character(len=50) :: format_str
        write (format_str, "('(', I0, 'F8.3)')") size(matrix, 2)
        do i = 1, size(matrix, 1)
            print format_str, matrix(i, :)
        end do
    end subroutine print_matrix

end module matrix_mod
