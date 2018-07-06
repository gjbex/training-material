program array_bounds
use, intrinsic :: iso_fortran_env, only : dp => REAL64
implicit none
real(kind=dp) :: a(16), total
integer :: i

total = 0.0_dp

do i  = 16, 0, -1
    a(i) = 3.0_dp*i
    total = total + a(i)
end do

print '(A, F8.1)', 'total ', total

end program array_bounds
