module gauss_mod
    use, intrinsic :: iso_fortran_env, only : dp => REAL64
    use :: quad_mod
    implicit none

    private
    type, public, extends(quad_type) :: gauss_type
        private
        real(kind=dp), dimension(10) :: xs, ws
    contains
        procedure, public :: init
        procedure, public :: integrate
    end type gauss_type

contains

    subroutine init(self)
        implicit none
        class(gauss_type), intent(inout) :: self
        self%ws(1)  = 0.2955242247147529; self%xs(1)  = -0.1488743389816312
        self%ws(2)  = 0.2955242247147529; self%xs(2)  =  0.1488743389816312
        self%ws(3)  = 0.2692667193099963; self%xs(3)  = -0.4333953941292472
        self%ws(4)  = 0.2692667193099963; self%xs(4)  =  0.4333953941292472
        self%ws(5)  = 0.2190863625159820; self%xs(5)  = -0.6794095682990244
        self%ws(6)  = 0.2190863625159820; self%xs(6)  =  0.6794095682990244
        self%ws(7)  = 0.1494513491505806; self%xs(7)  = -0.8650633666889845
        self%ws(8)  = 0.1494513491505806; self%xs(8)  =  0.8650633666889845
        self%ws(9)  = 0.0666713443086881; self%xs(9)  = -0.9739065285171717
        self%ws(10) = 0.0666713443086881; self%xs(10) =  0.9739065285171717
    end subroutine init

    function integrate(self, f, a, b) result(r)
        use :: quad_func_interface
        implicit none
        class(gauss_type), intent(in) :: self
        procedure(quad_func_type) :: f
        real(kind=dp), intent(in) :: a, b
        real(kind=dp) :: r
        real(kind=dp) :: x, delta
        integer :: i
        x = 0.5*(a + b)
        delta = 0.5*(b - a)
        r = 0.0_dp
        do i = 1, size(self%xs)
            r = r + self%ws(i)*f(x + self%xs(i)*delta)
        end do
        r = r*delta
    end function integrate


end module gauss_mod
