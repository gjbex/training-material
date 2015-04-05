program elemental_test
    use, intrinsic :: iso_fortran_env
    implicit none
    integer, parameter :: n = 16
    integer :: i
    integer(kind=INT64), dimension(n) :: input = [ (i, i = 0, n - 1) ], &
                                         output

    output = factorial(input)

    do i = 1, n
        print '(I2, I20)', input(i), output(i)
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

end program elemental_test
