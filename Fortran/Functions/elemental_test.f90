program elemental_test
    use, intrinsic :: iso_fortran_env, only : INT32, INT64, REAL64
    implicit none
    integer, parameter :: n = 16, p = 6
    integer :: i
    integer(kind=INT64), dimension(n) :: input = [ (i - 1, i = 1, n) ], &
                                         output
    real(kind=REAL64), dimension(p) :: x = [ (real(i - 1, kind=REAL64), &
                                              i = 1, p) ], &
                                       y
    integer(kind=INT64), dimension(p) :: degree = [ (i - 1, i = 1, p) ]

    print '(A)', '# factorial'
    output = factorial(input)
    do i = 1, n
        print '(I2, I20)', input(i), output(i)
    end do

    print '(A)', '# in place factorial'
    call in_place_factorial(input)
    do i = 1, n
        print '(I2, I20)', i, input(i)
    end do

    print '(A)', '# powers'
    y = power(x, degree)
    do i = 1, p
        print '(F8.2, I4, F20.2)', x(i), degree(i), y(i)
    end do

contains

    elemental function factorial(n) result(fac)
        implicit none
        integer(kind=INT64), intent(in) :: n
        integer(kind=INT64) :: fac
        integer(kind=INT32) :: i
        fac = 1
        do i = 2, n
            fac = fac*i
        end do
    end function factorial

    elemental subroutine in_place_factorial(i)
        implicit none
        integer(kind=int64), intent(inout) :: i
        i = factorial(i)
    end subroutine in_place_factorial

    elemental function power(x, n) result(y)
        implicit none
        real(kind=REAL64), intent(in) :: x
        integer(kind=INT64), intent(in) :: n
        real(kind=REAL64) :: y
        y = x**n
    end function power

end program elemental_test
