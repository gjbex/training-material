program compute_pi
    use, intrinsic :: iso_fortran_env, only : i8 => INT64, r8 => REAL64
    use omp_lib
    implicit none
    integer(kind=i8), parameter :: nr_tries = 1000000_i8, &
                                   nr_blocks = 10
    integer(kind=i8) :: partial_nr_tries, i
    real(kind=r8) :: nr_success
    integer :: num_threads, thread_num
    num_threads = 1
    thread_num = 0
    nr_success = 0.0_r8
    !$omp parallel private(thread_num, i, partial_nr_tries)
        !$ num_threads = omp_get_num_threads()
        !$ thread_num = omp_get_thread_num()
        print '(2(A, I2))', 'thread ', thread_num, ' of ', num_threads
        partial_nr_tries = nr_tries/(num_threads*nr_blocks)
        !$omp do reduction (+:nr_success)
            do i = 1, num_threads*nr_blocks
                nr_success = nr_success + &
                                 compute_partial_pi(partial_nr_tries)
            end do
        !$omp end do
    !$omp end parallel
    print '(A, F15.8)', 'pi =', 4.0_r8*nr_success/(num_threads*nr_blocks)

    contains

        real(kind=r8) function compute_partial_pi(nr_tries)
            implicit none
            integer(kind=i8), intent(in) :: nr_tries
            real(kind=r8) :: nr_success, x, y 
            integer(kind=i8) :: i
            nr_success = 0
            do i = 1_i8, nr_tries
                call random_number(x)
                call random_number(y)
                if (x**2 + y**2 < 1.0_r8) then
                    nr_success = nr_success + 1.0_r8
                end if
            end do
            compute_partial_pi = nr_success/nr_tries
        end function compute_partial_pi

end program compute_pi
