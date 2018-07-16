program matrix_bounds
use, intrinsic :: iso_fortran_env, only : dp => REAL64
use matrix_mod
implicit none
integer, parameter :: rows = 3, cols = 2
integer :: i, j, k, istat
real(kind=dp), dimension(:, :), allocatable :: B, A, C
real(kind=dp) :: r

allocate(B(rows, cols)) 
allocate(A(rows, cols))
allocate(C(rows, rows)) 

do i = 1, rows
    do j = 1, cols
        call random_number(r)
        A(i, j) = r
        call random_number(r)
        B(i, j) = r
    end do
end do

do i = 1, rows
    do j = 1, rows
        C(i, j) = 0.0_dp
        do k = 1, cols
            C(i, j) = C(i, j) + A(i, k)*B(k, j)
        end do
    end do
end do

call print_matrix(C)
print '(A, F15.8)', 'sum = ', sum(C)

deallocate(A)
deallocate(B)
deallocate(C)

end program matrix_bounds
