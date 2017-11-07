program implicit_not_none

    integer, parameter :: n = 5
    integer, dimension(n) :: a
    integer :: i
    real :: x

    do i = 1, n
        a(i) = i
    end do

    x = 5.3
    i = 5
    do while (x > 1.0)
        y = int(x)
        print *, y, y*a(i)
        x = x - 0.7
    end do
end program implicit_not_none
