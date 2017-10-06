program array_bounds_check
    implicit none
    integer, parameter :: n = 5
    integer, dimension(n) :: x
    integer :: i
    do i = 1, n + 1
        x(i) = i**2
    end do
    do i = 1, n + 1
        print '(I2, I3)', x(i)
    end do
end program array_bounds_check
