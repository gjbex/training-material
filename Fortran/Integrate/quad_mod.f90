module quad_mod
    implicit none

    type, abstract, public :: quad_type
    contains
        procedure(integrate_func_type), deferred :: integrate
    end type quad_type

    abstract interface
        function integrate_func_type(self, f, a, b) result(r)
            use, intrinsic :: iso_fortran_env, only : dp => REAL64
            use quad_func_interface
            import quad_type
            implicit none
            class(quad_type), intent(in) :: self
            procedure(quad_func_type) :: f
            real(kind=dp), intent(in) :: a, b
            real(kind=dp) :: r
        end function integrate_func_type
    end interface

end module quad_mod
