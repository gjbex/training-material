program initialization_test
    implicit none
    integer, parameter :: n = 5
    integer :: i

    print '(A1, 2A10)', 'n', 'wrong', 'right'
    do i = 0, n
        print '(I1, 2I10)', i, factorial_bad(i), factorial_good(i)
    end do

contains

    function factorial_bad(n) result(f)
        implicit none
        integer, intent(in) :: n
        integer :: f
        integer :: fac = 1, i
        do i = 2, n
            fac = fac*i
        end do
        f = fac
    end function factorial_bad

    function factorial_good(n) result(f)
        implicit none
        integer, intent(in) :: n
        integer :: f
        integer :: fac, i
        fac = 1
        do i = 2, n
            fac = fac*i
        end do
        f = fac
    end function factorial_good

end program initialization_test
