module simpson_mod
    use :: quad_mod
    implicit none

    private
    type, public, extends(quad_type) :: simpson_type
        private
        integer :: n
    contains
        procedure, public :: init
        procedure, public :: integrate
    end type simpson_type

contains

    subroutine init(self, n)
        implicit none
        class(simpson_type), intent(inout) :: self
        integer, intent(In) :: n
        self%n = n
    end subroutine init

    function integrate(self, f, a, b) result(r)
        use, intrinsic :: iso_fortran_env, only : dp => REAL64
        use :: quad_func_interface
        implicit none
        class(simpson_type), intent(in) :: self
        procedure(quad_func_type) :: f
        real(kind=dp), intent(in) :: a, b
        real(kind=dp) :: r
        real(kind=dp) :: x, delta
        integer :: i
        x = a
        r = f(x)
        delta = (b - a)/self%n
        do i = 1, self%n
            x = x + delta
            r = r + f(x)
        end do
        r = (b - a)*r/(self%n + 1)
    end function integrate


end module simpson_mod
