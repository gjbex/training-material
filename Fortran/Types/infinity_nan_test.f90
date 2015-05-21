program infinity_nan_test
    use, intrinsic :: iso_fortran_env, only : REAL32
    implicit none
    real(kind=REAL32) :: x, y
    real(kind=REAL32) :: x_delta = 1e32_REAL32

    x = huge(real(0.0, kind=REAL32))
    y = x + x_delta
    print "(E13.7, ' + ', E7.1, ' = ', F8.7)", x, x_delta, y
    call check_ieee(y)
    x = -1.0e20_REAL32
    y = 1.0e20_REAL32*x
    print "(E8.1, '*', E7.1, ' = ', F9.1)", x, y, y
    call check_ieee(y)
    x = 1.0e6_REAL32
    y = exp(x)
    print "(A, '(', E7.1, ') = ', F8.1)", 'exp', x, y
    call check_ieee(y)
    x = 0.0_REAL32
    y = log(x)
    print "(A, '(', F3.1, ') = ', F9.1)", 'log', x, y
    call check_ieee(y)
    x = 0.0_REAL32
    y = x/x
    print "(F3.1, '/', F3.1, ' = ', F3.1)", x, x, y
    call check_ieee(y)
    x = -1.0_REAL32
    y = sqrt(x)
    print "(A, '(', F4.1, ') = ', F3.1)", 'sqrt', x, y
    call check_ieee(y)

contains

    subroutine check_ieee(x)
#ifdef IEEE_STUFF
        use, intrinsic :: ieee_arithmetic
#endif
        implicit none
        real(kind=REAL32), intent(in) :: x
        character :: tab
        tab = char(9)
#ifdef IEEE_STUFF
        if (.not. ieee_is_finite(y)) &
            print '(2A)', tab, "IEEE not finite"
        if (ieee_is_nan(y)) &
            print '(2A)', tab, "IEEE NaN"
        if (.not. ieee_is_normal(y)) &
            print '(2A)', tab, "IEEE not normal"
#endif
    end subroutine check_ieee

end program infinity_nan_test
