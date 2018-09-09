program ieee_functions
    use, intrinsic :: ieee_arithmetic
    implicit none
    real :: result, r

    call random_number(r)  

    result = 1.0/min(0.0, r)
    print '(A, E10.5)', '1.0/0.0 =', result
    if (.not. ieee_is_finite(result)) then
        print '(A)', 'Infinity found'
    end if

    result = 0.0/min(0.0, r)
    print '(A, E10.5)', '1.0/0.0 =', result
    if (ieee_is_nan(result)) then
        print '(A)', 'NaN found'
    end if
end program ieee_functions

