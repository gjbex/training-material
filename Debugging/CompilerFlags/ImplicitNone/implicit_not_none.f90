program implicit_none

    integer, parameter :: n = 5
    integer, dimension(n) :: a

    do i = 1, n
        a(i) = i
    end do

    k = 5.9
    i = 5
    do while (k >= 1.0)
        m = k
        k = k - 1.01
        print *, m, m*a(i)
    end do

end program implicit_none
