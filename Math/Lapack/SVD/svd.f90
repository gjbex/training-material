program svd
use utils_mod, only : get_file_name, get_dataset_name
use matrix_mod, only : read_matrix, print_matrix
use, intrinsic :: iso_fortran_env, only : dp => REAL64, error_unit
implicit none
logical, parameter :: verbose = .false.
real(kind=dp), allocatable, dimension(:, :) :: A, U, VT, Sigma, orig_A, tmp
real(kind=dp), allocatable, dimension(:) :: S, work
character(len=1024) :: file_name, dataset_name
integer :: nr_rows, nr_cols, lda, ldu, error, lwork, info

call get_file_name(file_name)
call get_dataset_name(dataset_name)
call read_matrix(file_name, dataset_name, A)
nr_rows = size(A, 1)
nr_cols = size(A, 2)

! copy A, since it will be destroyed by dgesvd
allocate(orig_A(nr_rows, nr_cols), stat=error)
if (error /= 0) then
    write (unit=error_unit, fmt="(A)") "can not allocate orig_A"
    stop
end if
orig_A = A

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

! cmopute full SVD of A
allocate(work(1))
info = 0
call dgesvd('A', 'A', nr_rows, nr_cols, A, nr_rows, S, &
            U, nr_rows, VT, nr_cols, work, -1, info)
lwork = work(1)
deallocate(work)
allocate(work(lwork))
if (error /= 0) then
    write (unit=error_unit, fmt="(A)") "can not allocate work"
    stop
end if
call dgesvd('A', 'A', nr_rows, nr_cols, A, nr_rows, S, &
            U, nr_rows, VT, nr_cols, work, lwork, info)
call compute_sigma(S, nr_rows, nr_cols, sigma)
deallocate(work)

! print results if verbose
if (verbose) then
    print "(A)", "U"
    call print_matrix(U)
    print "(A)", "Sigma"
    call print_matrix(Sigma)
    print "(A)", "V^t"
    call print_matrix(VT)
end if

! perform check
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

! print reconstructted and original matrix if verbose
if (verbose) then
    print "(A)", "A"
    call print_matrix(A)
    print "(A)", "orig. A"
    call print_matrix(orig_A)
end if

! compute and print relative error
print "(A, E10.3)", 'relative error = ', compute_error(orig_A, A)

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
