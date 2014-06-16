module math_func_mod
    implicit none

    interface
        function math_func(x) result(r)
            double precision, intent(in) :: x
            double precision :: r
        end function math_func
    end interface
    type, public :: func_record
        procedure(math_func), pointer, nopass :: f => null()
        character(len=50) :: name
    end type func_record
    type(func_record), dimension(3) :: functions

contains

    subroutine setup()
        implicit none
        functions(1)%f => f1
        functions(1)%name = "x**2"
        functions(2)%f => f2
        functions(2)%name = "sqrt(x)"
        functions(3)%f => f3
        functions(3)%name = "exp(x)"
    end subroutine setup

    function f1(x) result(r)
        implicit none
        double precision, intent(in) :: x
        double precision :: r
        r = x**2
    end function f1

    function f2(x) result(r)
        implicit none
        double precision, intent(in) :: x
        double precision :: r
        r = sqrt(x)
    end function f2

    function f3(x) result(r)
        implicit none
        double precision, intent(in) :: x
        double precision :: r
        r = exp(x)
    end function f3
    
end module math_func_mod
