program implicit_none

    integer, parameter :: n = 5
    integer, dimension(n) :: a
    integer :: i
    real :: p, m

    do i = 1, n
        a(i) = i
    end do

    p = 5.9
    i = 5
    do while (p >= 1.0)
        m = p
        print *, m, m*a(i)
        p = p - 1.01
    end do

end program implicit_none
