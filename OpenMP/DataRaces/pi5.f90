program compute_pi
    use, intrinsic :: iso_fortran_env, only : dp => REAL64
    use omp_lib
    implicit none
    integer, parameter :: num_iters = 1000
    integer :: i
    real(kind=dp) :: x, pi_sum, dx, pi

    pi_sum = 0.0_dp
    dx = 1.0_dp/num_iters
    !$omp parallel private(x), shared(dx, pi_sum), default(none)
    !$omp do reduction(+:pi_sum) schedule(runtime)
    do i = 1, num_iters
        x = i*dx
        pi_sum = pi_sum + 1.0_dp/(1.0_dp + x**2)        
    end do
    !$end omp do
    !$omp end parallel
    pi = 4.0_dp*pi_sum*dx
    print '(E10.7)', pi
end program compute_pi
