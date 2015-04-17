program subarray_test
    use, intrinsic :: iso_fortran_env
    use matrix_ops
    implicit none
    integer, parameter :: m = 4, n = 5, dp = REAL64
    real(kind=dp), dimension(m, n) :: a
    real(kind=dp), dimension(m/2, n/2) :: b
    real(kind=dp), dimension(m -2) :: v
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
    a(2:3, 2:4) = 0.0_dp
    call print_matrix(a, 'A')
    b = a(1:m:2, 1:n:3)
    call print_matrix(b, 'B')
    b = a(::2, ::3)
    call print_matrix(b, 'B')
    v = a(3:, 1)
    call print_vector(v, 'v')

end program subarray_test
