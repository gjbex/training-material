program compute_pi
    use omp_lib
    implicit none
    integer, parameter :: num_iters = 1000
    integer :: i
    real :: x, pi_sum, dx, pi

    pi_sum = 0.0
    dx = 1.0/num_iters
    !$omp parallel private(x), shared(dx, pi_sum), default(none)
    !$omp do reduction(+:pi_sum) schedule(runtime)
    do i = 1, num_iters
        x = i*dx
        pi_sum = pi_sum + 1.0/(1.0 + x**2)        
    end do
    !$end omp do
    !$omp end parallel
    pi = 4.0*pi_sum*dx
    print *, pi
end program compute_pi
