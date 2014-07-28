module internals_mod
    implicit none
    private
    public :: compute_more

contains

    subroutine compute_more(n, s)
        implicit none
        integer, intent(in) :: n
        real, intent(out) :: s
        integer :: i
        real :: x = 0.5
        s = 0.0
        do i = 1, n
            s = s + my_pow(x)
        end do
    
    contains

        function my_pow(y) result(p)
            implicit none
            real, intent(in) :: y
            real :: p
            real, save :: x = 0.0
            p = y**i
            print "(A, F4.1)", "local x = ", x
            x = x + 1.5
        end function my_pow

    end subroutine compute_more

end module internals_mod
