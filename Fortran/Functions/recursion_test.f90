module funcs_mod
    implicit none

    private
    public :: factorial

contains

    recursive function factorial(n) result(f)
        implicit none
        integer, intent(in) :: n
        integer :: f
        if (n < 2) then
            f = 1
        else
            f = n*factorial(n - 1)
        end if
    end function factorial

end module funcs_mod

program recursion_test
    use :: funcs_mod, only : factorial
    implicit none
    integer, parameter :: n_min = 0, n_max = 6
    integer :: i

    do i = n_min, n_max
        print *, i, factorial(i)
    end do

end program recursion_test
