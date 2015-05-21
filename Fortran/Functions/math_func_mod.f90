module math_func_mod
    use, intrinsic :: iso_fortran_env, only : REAL64
    use math_func_interface
    implicit none

    private
    type, public :: func_record
        procedure(math_func), pointer, nopass :: f => null()
        character(len=50) :: name
    end type func_record
    type(func_record), public, dimension(9) :: functions
    public :: setup

contains

    subroutine setup()
        implicit none
        functions(1)%f => f7
        functions(1)%name = 'x + x'
        functions(2)%f => f6
        functions(2)%name = "x*x"
        functions(3)%f => f8
        functions(3)%name = "2.13/x"
        functions(4)%f => f1
        functions(4)%name = "x**2"
        functions(5)%f => f5
        functions(5)%name = "x**2.1D00"
        functions(6)%f => f2
        functions(6)%name = "sqrt(x)"
        functions(7)%f => f3
        functions(7)%name = "exp(x)"
        functions(8)%f => f4
        functions(8)%name = "erf(x)"
        functions(9)%f => f9
        functions(9)%name = "x*x + x"
    end subroutine setup

    function f1(x) result(r)
        implicit none
        real(kind=REAL64), intent(in) :: x
        real(kind=REAL64) :: r
        r = x**2
    end function f1

    function f2(x) result(r)
        implicit none
        real(kind=REAL64), intent(in) :: x
        real(kind=REAL64) :: r
        r = sqrt(x)
    end function f2

    function f3(x) result(r)
        implicit none
        real(kind=REAL64), intent(in) :: x
        real(kind=REAL64) :: r
        r = exp(x)
    end function f3
    
    function f4(x) result(r)
        implicit none
        real(kind=REAL64), intent(in) :: x
        real(kind=REAL64) :: r
        r = erf(x)
    end function f4
    
    function f5(x) result(r)
        implicit none
        real(kind=REAL64), intent(in) :: x
        real(kind=REAL64) :: r
        r = x**2.1D00
    end function f5
    
    function f6(x) result(r)
        implicit none
        real(kind=REAL64), intent(in) :: x
        real(kind=REAL64) :: r
        r = x*x
    end function f6
    
    function f7(x) result(r)
        implicit none
        real(kind=REAL64), intent(in) :: x
        real(kind=REAL64) :: r
        r = x + x
    end function f7

    function f8(x) result(r)
        implicit none
        real(kind=REAL64), intent(in) :: x
        real(kind=REAL64) :: r
        r = 2.13/x
    end function f8

    function f9(x) result(r)
        implicit none
        real(kind=REAL64), intent(in) :: x
        real(kind=REAL64) :: r
        r = x*x + x
    end function f9

end module math_func_mod
