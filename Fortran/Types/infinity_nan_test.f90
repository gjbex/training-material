program infinity_nan_test
    use, intrinsic :: iso_fortran_env
    implicit none
    real(kind=REAL32) :: x, y
    real(kind=REAL32) :: x_delta = 1e32_REAL32

    x = huge(real(0.0, kind=REAL32))
    print "(E13.7, ' + ', E7.1, ' = ', F8.7)", x, x_delta, x + x_delta
    x = -1.0e20_REAL32
    y = 1.0e20_REAL32
    print "(E8.1, '*', E7.1, ' = ', F9.1)", x, y, x*y
    x = 1.0e6_REAL32
    print "(A, '(', E7.1, ') = ', F8.1)", 'exp', x, exp(x)
    x = 0.0_REAL32
    print "(A, '(', F3.1, ') = ', F9.1)", 'log', x, log(x)
    x = 0.0_REAL32
    print "(F3.1, '/', F3.1, ' = ', F3.1)", x, x, x/x
    x = -1.0_REAL32
    print "(A, '(', F4.1, ') = ', F3.1)", 'sqrt', x, sqrt(x)

end program infinity_nan_test
