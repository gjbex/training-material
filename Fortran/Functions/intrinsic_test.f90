program intrinsic_test
    use, intrinsic :: iso_fortran_env
    implicit none
    integer, parameter :: dp = REAL64, m = 2, n = 3
    real(kind=dp), dimension(m, n) :: r

    call random_number(r)
    print '(F10.8)', r

end program intrinsic_test
