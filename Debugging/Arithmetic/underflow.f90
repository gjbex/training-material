program underflow

    use, intrinsic :: iso_fortran_env, only : sp => REAL32, dp => REAL64
    implicit none
    integer, parameter :: n = 5
    real(kind=sp), dimension(n) :: x = [ 1.0e-31_sp, 1.0e-31_sp, 5.0_sp, &
                                         1.0e31_sp, 1.0e31_sp ]
    integer :: i;
    real(kind=sp) :: prod
    real(kind=sp) :: log_prod
    real(kind=dp) :: dprod
    prod = 1.0_sp
    log_prod = 0.0_sp
    dprod = 1.0_dp
    do i = 1, n
        prod = prod*x(i)
    end do
    do i = 1, n
        dprod = dprod*x(i)
    end do
    do i = 1, n
        log_prod = log_prod + log(x(i))
    end do
    print '(A, F20.15)', 'REAL32 product = ', prod
    print '(A, F20.15)', 'REAL64 product = ', dprod
    print '(A, F20.15)', 'log REAL32 product = ', exp(log_prod)
    prod = 1.0_sp;
    do i = 1, n
        prod = prod*x(i)
    end do
    print '(A, F20.15)', 'REAL32 product (reverse) = ', prod

end program underflow
