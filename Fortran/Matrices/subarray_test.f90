program subarray_test
    use, intrinsic :: iso_fortran_env
    use matrix_ops
    implicit none
    integer, parameter :: m = 4, n = 5, dp = REAL64
    real(kind=dp), dimension(m, n) :: a
    integer :: i, j

    do j = 1, n
        do i = 1, m
            a(i, j) = j + (i - 1)*n
        end do
    end do
    call print_matrix(a, 'A')
    call print_vector(a(2, :), 'row 2 of A')
    call print_vector(a(:, 3), 'column 3 of A')
    call print_matrix(a(2:3, 2:4), 'subarray of A')

end program subarray_test
