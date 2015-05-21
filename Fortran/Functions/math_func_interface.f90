module math_func_interface
    implicit none

    interface
        function math_func(x) result(r)
            use, intrinsic :: iso_fortran_env, only : REAL64
            real(kind=REAL64), intent(in) :: x
            real(kind=REAL64) :: r
        end function math_func
    end interface

end module math_func_interface
