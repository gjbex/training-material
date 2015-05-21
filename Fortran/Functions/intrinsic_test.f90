program intrinsic_test
    use, intrinsic :: iso_fortran_env, only : dp => REAL64
    implicit none
    integer, parameter :: m = 2, n = 3
    real(kind=dp), dimension(m, n) :: r

    call random_number(r)
    print '(F10.8)', r

end program intrinsic_test
