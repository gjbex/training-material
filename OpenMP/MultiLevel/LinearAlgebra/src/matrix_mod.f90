module matrix_mod
implicit none

contains

    subroutine compute_sigma(S, nr_rows, nr_cols, Sigma)
        use, intrinsic :: iso_fortran_env, only : dp => REAL64
        implicit none
        real(kind=dp), dimension(:), intent(in) :: S
        integer, intent(in) :: nr_rows, nr_cols
        integer :: i, error
        real(kind=dp), allocatable, dimension(:, :), intent(out) :: Sigma
        allocate(Sigma(nr_rows, nr_cols), stat=error)
        Sigma = 0.0_dp
        do i = 1, min(nr_rows, nr_cols)
            Sigma(i, i) = S(i)
        end do
    end subroutine compute_sigma

    subroutine reconstruct_matrix(U, S, VT, A)
        use, intrinsic :: iso_fortran_env, only : dp => REAL64, error_unit
        implicit none
        real(kind=dp), dimension(:, :), intent(in) :: U, VT
        real(kind=dp), dimension(:), intent(in) :: S
        real(kind=dp), dimension(:, :), allocatable, intent(out) :: A
        real(kind=dp), dimension(:, :), allocatable :: tmp, Sigma
        integer :: nr_rows, nr_cols, error

        ! create Sigma
        nr_rows = size(U, 1)
        nr_cols = size(VT, 2)
        call compute_sigma(S, nr_rows, nr_cols, Sigma)
        
        ! allocate reconstructed matrix
        allocate(A(nr_rows, nr_cols), stat=error)
        if (error /= 0) then
            write (unit=error_unit, fmt="(A)") "can not allocate A"
            stop
        end if

        ! compute tmp = U*Sigma
        allocate(tmp(nr_rows, nr_cols), stat=error)
        if (error /= 0) then
            write (unit=error_unit, fmt="(A)") "can not allocate work"
            stop
        end if
        call dgemm('N', 'N', nr_rows, nr_cols, nr_rows, 1.0_dp, U, nr_rows, &
                   Sigma, nr_rows, 0.0_dp, tmp, nr_rows)
        call dgemm('N', 'N', nr_rows, nr_cols, nr_cols, 1.0_dp, tmp, nr_rows, &
                   VT, nr_cols, 0.0_dp, A, nr_rows)

        ! clean up
        deallocate(Sigma, tmp)

    end subroutine reconstruct_matrix

    subroutine compute_svd(A_orig, U, S, Vt)
        use, intrinsic :: iso_fortran_env, only : dp => REAL64, i8 => INT64, &
                                                  error_unit
        implicit none
        real(kind=dp), dimension(:, :), intent(in) :: A_orig
        real(kind=dp), dimension(:, :), allocatable, intent(out) :: U, VT
        real(kind=dp), dimension(:), allocatable, intent(out) :: S
        real(kind=dp), dimension(:), allocatable :: work
        real(kind=dp), dimension(:, :), allocatable :: A
        integer :: nr_rows, nr_cols, error, info, lwork

        nr_rows = size(A_orig, 1)
        nr_cols = size(A_orig, 2)

        ! copy A, since it will be destroyed by dgesvd
        allocate(A, source=A_orig, stat=error)
        if (error /= 0) then
            write (unit=error_unit, fmt="(A)") "can not allocate orig_A"
            stop
        end if
        A = A_orig

        ! allocate matricess
        allocate(U(nr_rows, nr_rows), stat=error)
        if (error /= 0) then
            write (unit=error_unit, fmt="(A)") "can not allocate U"
            stop
        end if
        allocate(S(min(nr_rows, nr_cols)), stat=error)
        if (error /= 0) then
            write (unit=error_unit, fmt="(A)") "can not allocate S"
            stop
        end if
        allocate(VT(nr_cols, nr_cols), stat=error)
        if (error /= 0) then
            write (unit=error_unit, fmt="(A)") "can not allocate VT"
            stop
        end if

        ! compute full SVD of A
        allocate(work(1))
        info = 0
        call dgesvd('A', 'A', nr_rows, nr_cols, A, nr_rows, S, &
                    U, nr_rows, VT, nr_cols, work, -1, info)
        lwork = int(work(1))
        deallocate(work)
        allocate(work(lwork), stat=error)
        if (error /= 0) then
            write (unit=error_unit, fmt="(A)") "can not allocate work"
            stop
        end if
        call dgesvd('A', 'A', nr_rows, nr_cols, A, nr_rows, S, &
                    U, nr_rows, VT, nr_cols, work, lwork, info)

        ! clean up
        deallocate(A)
        deallocate(work)

    end subroutine compute_svd

    subroutine get_matrix_dimensions(file_name, matrix_dset_name, &
                                     dims)
        use hdf5
        use, intrinsic :: iso_fortran_env, only : dp => REAL64, error_unit
        implicit none
        integer, parameter :: matrix_rank = 2
        character(len=*), intent(in) :: file_name, matrix_dset_name
        integer, dimension(matrix_rank) :: dims
        integer(hid_t) :: file_id, matrix_dset_id, matrix_fspace_id
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
        integer(hid_t) :: file_id, matrix_dset_id, matrix_mspace_id, matrix_fspace_id
        integer, parameter :: matrix_rank = 2
        integer(hsize_t), dimension(matrix_rank) :: matrix_dims, &
                                                    max_matrix_dims
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
                "matrix can not be allocated"
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
