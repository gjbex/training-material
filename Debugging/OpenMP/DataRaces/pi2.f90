program compute_pi
    use omp_lib
    implicit none
    integer, parameter :: num_iters = 1000
    integer :: i, thread_num, num_threads
    real :: x, pi_sum, dx, pi

    pi_sum = 0.0
    dx = 1.0/num_iters
    num_threads = 1
    thread_num = 0
    !$omp parallel private(x)
    !$ num_threads = omp_get_num_threads()
    !$ thread_num = omp_get_thread_num()
    x = real(thread_num)*num_iters/num_threads
    !$omp do reduction(+:pi_sum)
    do i = 1, num_iters
        x = x + dx
        pi_sum = pi_sum + 1.0/(1.0 + x**2)        
    end do
    !$end omp do
    !$omp end parallel
    pi = 4.0*pi_sum*dx
    print *, pi
end program compute_pi
