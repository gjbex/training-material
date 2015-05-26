module gauss_mod
    use, intrinsic :: iso_fortran_env, only : dp => REAL64
    use :: quad_mod
    implicit none

    private
    type, public, extends(quad_type) :: gen_gauss_type
        private
        real(kind=dp) :: precision
        real(kind=dp), dimension(:), allocatable :: ws, xs
    contains
        private
        procedure, public :: init_gen_gauss
        procedure :: init_vectors
        procedure, public :: integrate
        procedure, public :: print_params
    end type gen_gauss_type

    real(kind=dp), parameter :: pi = 3.1415926535897932384626_dp, &
                                default_precision = 1.0e-10_dp

    integer, parameter :: nr_points = 10
    
    type, public, extends(gen_gauss_type) :: gauss_type
    contains
        private
        procedure, public :: init => init_gauss10
    end type gauss_type

contains

    subroutine init_gauss10(self)
        implicit none
        class(gauss_type), intent(inout) :: self
        call self%init_vectors(nr_points)
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
    end subroutine init_gauss10

    subroutine init_vectors(self, n, stat)
        implicit none
        class(gen_gauss_type), intent(inout) :: self
        integer, intent(in) :: n
        integer, intent(inout), optional :: stat
        integer :: istat
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
    end subroutine init_vectors

    subroutine init_gen_gauss(self, n, precision, stat)
        implicit none
        class(gen_gauss_type), intent(inout) :: self
        integer, intent(in) :: n
        real(kind=dp), intent(in), optional :: precision
        integer, intent(inout), optional :: stat
        integer :: istat, i
        real(kind=dp) :: z, z1, pp
        if (present(precision)) then
            self%precision = precision
        else
            self%precision = default_precision
        end if
        call self%init_vectors(n)
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

    end subroutine init_gen_gauss

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

    subroutine print_params(self)
        implicit none
        class(gen_gauss_type), intent(in) :: self
        integer :: i
        do i = 1, size(self%xs)
            print '(2F20.15)', self%xs(i), self%ws(i)
        end do
    end subroutine print_params

end module gauss_mod
