program integration_test
    use, intrinsic :: iso_fortran_env, only : dp => REAL64
    use :: quad_mod, only : quad_type
    use :: simpson_mod, only : simpson_type
    use :: gauss_mod, only : gauss_type
    implicit none
    integer, parameter :: nr_quads = 5
    type(simpson_type), dimension(nr_quads) :: simpson_quads
    type(simpson_type), target :: simpson_quad
    type(gauss_type), target :: gauss_quad
    class(quad_type), pointer :: quad
    real(kind=dp), parameter :: a = -1.0_dp, b = 2.0_dp
    integer, parameter :: n0 = 10
    integer :: i
    logical :: do_gauss
    character(len=1024) :: buffer
    if (command_argument_count() >= 1) then
        call get_command_argument(1, buffer)
        do_gauss = trim(buffer) == 'gauss'
    else
        do_gauss = .true.
        buffer = 'gauss'
    end if
    do i = 1, nr_quads
        call simpson_quads(i)%init(n0**i)
    end do
    print '(A)', 'Simpson:'
    do i = 1, nr_quads
        print '(I6, F10.4)', n0**i, simpson_quads(i)%integrate(f, a, b)
    end do

    call gauss_quad%init()
    print '(A)', 'Gauss-Legendre:'
    print '(F10.4)', gauss_quad%integrate(f, a, b)

    if (do_gauss) then
        call gauss_quad%init()
        quad => gauss_quad
    else
        call simpson_quad%init(10)
        quad => simpson_quad
    end if
    print '(A, F10.4)', trim(buffer), quad%integrate(f, -1.0_dp, 2.0_dp)

contains

    function f(x) result(r)
        implicit none
        real(kind=dp), intent(in) :: x
        real(kind=dp) :: r
        r = x**2
    end function f

end program integration_test
