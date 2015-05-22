module gen_gauss_mod
    use, intrinsic :: iso_fortran_env, only : dp => REAL64
    use :: quad_mod, only : quad_type
    implicit none

    private
    type, public, extends(quad_type) :: gen_gauss_type
        private
        real(kind=dp) :: precision
        real(kind=dp), dimension(:), allocatable :: ws, xs
    contains
        procedure, public :: init
        procedure, public :: integrate
        procedure, public :: print_params
    end type gen_gauss_type

    real(kind=dp), parameter :: pi = 3.1415926535897932384626_dp, &
                                default_precision = 1.0e-10_dp

contains

    subroutine init(self, n, precision, stat)
        implicit none
        class(gen_gauss_type), intent(inout) :: self
        integer, intent(in) :: n
        real(kind=dp), intent(in), optional :: precision
        integer, intent(out), optional :: stat
        integer :: istat, i
        real(kind=dp) :: z, z1, pp
        if (present(precision)) then
            self%precision = precision
        else
            self%precision = default_precision
        end if
        allocate(self%xs(n), stat=istat)
        if (istat /= 0) then
            if (present(stat)) then
                stat = istat
                return
            else
                stop 'can not allocate x values'
            end if
        end if
        allocate(self%ws(n), stat=istat)
        if (istat /= 0) then
            if (present(stat)) then
                stat = istat
                return
            else
                stop 'can not allocate w values'
            end if
        end if
        do i = 1, n
            z = cos(pi*(i - 0.25_dp)/(n + 0.5_dp))
            call compute_zs(z, z1, pp, n)
            do while ((z - z1) > self%precision)
                call compute_zs(z, z1, pp, n)
            end do
            self%xs(i) = -z
            self%ws(i) = 2.0_dp/((1.0_dp - z**2)*pp**2)
        end do
        
    contains

        subroutine compute_zs(z, z1, pp, n)
            implicit none
            real(kind=dp), intent(inout) :: z
            real(kind=dp), intent(out) :: z1, pp
            integer, intent(in) :: n
            integer :: i
            real(kind=dp) :: p1, p2, p3 
            p1 = 1.0_dp
            p2 = 0.0_dp
            do i = 1, n
                p3 = p2
                p2 = p1
                p1 = ((2*i - 1)*z*p2 - (i - 1)*p3)/i
            end do
            pp = n*(z*p1 - p2)/(z**2 - 1.0_dp)
            z1 = z
            z = z1 - p1/pp
        end subroutine compute_zs

    end subroutine init

    subroutine print_params(self)
        implicit none
        class(gen_gauss_type), intent(in) :: self
        integer :: i
        do i = 1, size(self%xs)
            print '(2F20.15)', self%xs(i), self%ws(i)
        end do
    end subroutine print_params

    function integrate(self, f, a, b) result(r)
        use :: quad_func_interface
        implicit none
        class(gen_gauss_type), intent(in) :: self
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

end module gen_gauss_mod
