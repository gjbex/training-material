program integer_division
    use, intrinsic :: iso_fortran_env, only : REAL64
    implicit none
    real(kind=REAL64) :: x
    x = 1/2
    print '(A, F3.1)', '1/2 = ', x
    x = 1.0/2.0
    print '(A, F3.1)', '1.0/2.0 = ', x
end program integer_division
