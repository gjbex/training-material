program integration_test
    use, intrinsic :: iso_fortran_env, only : dp => REAL64, error_unit
    use :: gauss_mod, only : gen_gauss_type
    implicit none
    type(gen_gauss_type) :: quad
    integer :: n
    real(kind=dp) :: a = -1.0_dp, b = 1.0_dp, eps = 1.0e-9_dp
    character(len=1024) :: buffer

    if (command_argument_count() >= 3) then
        call get_command_argument(1, buffer)
        read (buffer, fmt='(I10)') n
        call get_command_argument(2, buffer)
        read (buffer, fmt='(E25.15)') a
        call get_command_argument(3, buffer)
        read (buffer, fmt='(E25.15)') b
    else
        write (unit=error_unit, fmt='(A)') &
            '#error: three command line argument expected, n, a, and b'
    end if
    call quad%init_gen_gauss(n, eps)
    print '(F25.15)', quad%integrate(f, a, b)

contains

    function f(x) result(r)
        implicit none
        real(kind=dp), intent(in) :: x
        real(kind=dp) :: r
        r = cos(x**2)*exp(0.37_dp*x)/(x**2 + 17.0_dp)
    end function f

end program integration_test
