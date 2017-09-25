module quad_func_interface


    interface
        function quad_func_type(x) result(f)
            use, intrinsic :: iso_fortran_env, only : dp => REAL64
            implicit none
            real(kind=dp), intent(in) :: x
            real(kind=dp) :: f
        end function quad_func_type
    end interface

end module quad_func_interface
