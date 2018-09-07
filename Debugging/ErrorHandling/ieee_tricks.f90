program ieee_tricks
    implicit none
    real, parameter :: infinity = huge(real(0.0))
    real :: result, r

    call random_number(r)  
    result = 1.0/min(0.0, r)
    print '(A, E10.5)', '1.0/0.0 =', result
    if (result < -infinity .or. infinity < result) then
        print '(A)', 'Infinity found'
    end if

    result = 0.0/min(0.0, r)
    print '(A, E10.5)', '1.0/0.0 =', result
    if (result /= result) then
        print '(A)', 'NaN found'
    end if
end program ieee_tricks
