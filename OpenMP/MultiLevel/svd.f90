program svd
    use utils_mod, only : get_file_name, get_dataset_name
    use matrix_mod, only : read_matrix, print_matrix, compute_svd, &
                           reconstruct_matrix, compute_sigma
    use, intrinsic :: iso_fortran_env, only : dp => REAL64, &
                                              i8 => INT64, &
                                              error_unit
    implicit none
    logical, parameter :: verbose = .false.
    real(kind=dp), allocatable, dimension(:, :) :: A, U, VT, Sigma, orig_A
    real(kind=dp), allocatable, dimension(:) :: S
    character(len=1024) :: file_name, dataset_name
    integer :: nr_rows, nr_cols, error

    call get_file_name(file_name)
    call get_dataset_name(dataset_name)
    call read_matrix(file_name, dataset_name, A)
    nr_rows = size(A, 1)
    nr_cols = size(A, 2)

    ! compute SVD
    call compute_svd(A, U, S, VT)

    ! compute Sigma, which is nicer than S, and which is needed to
    ! reconstruct the matrix
    call compute_sigma(S, nr_rows, nr_cols, sigma)

    ! print results if verbose
    if (verbose) then
        print "(A)", "U"
        call print_matrix(U)
        print "(A)", "Sigma"
        call print_matrix(Sigma)
        print "(A)", "V^t"
        call print_matrix(VT)
    end if

    ! copy original matrix
    allocate(orig_A, source=A, stat=error)
    if (error /= 0) then
    end if
    orig_A = A
    deallocate(A)

    call reconstruct_matrix(U, S, VT, A)

    ! print reconstructted and original matrix if verbose
    if (verbose) then
        print "(A)", "A"
        call print_matrix(A)
        print "(A)", "orig. A"
        call print_matrix(orig_A)
    end if

    ! compute and print relative error
    print "(A, E10.3)", 'relative error = ', compute_error(orig_A, A)

    deallocate(A, orig_A, U, S, VT, Sigma)

contains

    function compute_error(orig_A, A) result(rel_err)
        use, intrinsic :: iso_fortran_env, only : dp => REAL64
        implicit none
        real(kind=dp), dimension(:, :), intent(in) :: orig_A, A
        real(kind=dp) :: rel_err
        integer :: i, j
        real(kind=dp) :: norm
        rel_err = 0.0_dp
        do j = 1, size(A, 2)
            do i = 1, size(A, 1)
                norm = abs(orig_A(i, j))
                rel_err = rel_err + abs(A(i, j) - orig_A(i, j))/norm
            end do
        end do
        rel_err = rel_err/(size(A, 1)*size(A, 2))
    end function compute_error

end program svd
