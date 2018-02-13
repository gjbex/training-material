module rationals_mod
    use, intrinsic :: iso_fortran_env
    implicit none

    private
    type, public :: rational
        private
        integer :: num = 1, denom = 1, sign = 1
    end type rational

    interface rational
        module procedure rat_create
    end interface rational

    interface operator(+)
        module procedure rat_add
    end interface

    interface operator(*)
        module procedure rat_mul, int_rat_mul
    end interface

    public :: rat_print, operator(+), operator(*)

contains

    type(rational) function rat_create(n, d)
        implicit none
        integer, value :: n, d
        integer :: g
        if (d == 0) then
            write (unit=error_unit, fmt='(A)') &
                "# error: denominator must be non-zero"
            stop
        end if
        if (n*d < 0) then
            rat_create%sign = -1
        else
            rat_create%sign = 1
        end if
        n = abs(n)
        d = abs(d)
        g = gcd(n, d)
        rat_create%num = n/g
        rat_create%denom = d/g
    end function rat_create

    type(rational) function rat_add(a, b)
        implicit none
        type(rational), intent(in) :: a, b
        rat_add = rat_create(a%sign*a%num*b%denom + b%sign*b%num*a%denom, &
                             a%denom*b%denom)
    end function rat_add

    type(rational) function rat_mul(a, b)
        implicit none
        type(rational), intent(in) :: a, b
        rat_mul = rat_create(a%sign*a%num*b%sign*b%num, a%denom*b%denom)
    end function rat_mul

    type(rational) function int_rat_mul(a, b)
        implicit none
        integer, intent(in) :: a
        type(rational), intent(in) :: b
        int_rat_mul = rat_create(a*b%sign*b%num, b%denom)
    end function int_rat_mul

    subroutine rat_print(a)
        implicit none
        type(rational), intent(in) :: a
        if (a%sign > 0) then
            write (*, "(I0, '/', I0)") a%num, a%denom
        else
            write (*, "('-', I0, '/', I0)") a%num, a%denom
        end if
    end subroutine rat_print

    integer function gcd(x, y)
        implicit none
        integer, value :: x, y
        x = abs(x)
        y = abs(y)
        do while (x /= y)
            if (x > y) then
                x = x - y
            else if (y > x) then
                y = y - x
            end if
        end do
        gcd = x
    end function gcd

end module rationals_mod
