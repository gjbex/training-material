module fac_mod
    implicit none
    public :: factorial
    
contains

    function factorial(n) result(fact)
        implicit none
        integer, intent(in) :: n
        integer :: fact
        integer :: fac = 1
        integer :: i
        do i = 2, n
            fac = fac*i
        end do
        fact = fac
    end function factorial

end module fac_mod
