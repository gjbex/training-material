module rationals_mod
implicit none

    private
    type, public :: rational
        private
        integer :: num, denom
    end type rational

    interface rational
        module procedure rat_create
    end interface rational

    interface operator(+)
        module procedure rat_add
    end interface

    public :: rat_print, operator(+)

contains

    type(rational) function rat_create(n, d)
        implicit none
        integer :: n, d
        rat_create%num = n
        if (d > 0) then
            rat_create%denom = d
        else
            print *, "denominator must be positive"
            stop
        end if
    end function rat_create

    type(rational) function rat_add(a, b)
        implicit none
        type(rational), intent(in) :: a, b
        type(rational) :: result
        rat_add%denom = a%denom*b%denom
        rat_add%num = a%num*b%denom + b%num*a%denom
    end function rat_add

    subroutine rat_print(a)
        implicit none
        type(rational), intent(in) :: a
        write (*, "(I0, '/', I0)") a%num, a%denom
    end subroutine rat_print

end module rationals_mod
