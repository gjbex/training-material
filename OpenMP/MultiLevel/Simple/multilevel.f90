program multilevel
    use :: omp_lib
    implicit none
    integer, dimension(100) :: ids
    integer :: outer_thread_id, inner_thread_id, level, &
               total_threads, abs_id

    total_threads = 0
    !$omp parallel private(outer_thread_id, inner_thread_id, level, abs_id) &
    !$omp          shared(ids, total_threads) default(none)

        outer_thread_id = omp_get_thread_num()
        level = omp_get_level()
        print '(A, I0, A, I0)', 'outer thread ', outer_thread_id, ' at ', level

        !$omp parallel private(inner_thread_id, level, abs_id) &
        !$omp          shared(ids, total_threads, outer_thread_id) &
        !$omp          default(none)

            !$omp critical
                total_threads = total_threads + 1
            !$omp end critical
            inner_thread_id = omp_get_thread_num()
            level = omp_get_level()
            print '(A, I0, A, I0, A, I0)', 'thread ', inner_thread_id, &
                                           ' in ', outer_thread_id, &
                                           ' at ', level
            abs_id = omp_get_num_threads()*outer_thread_id + &
                     inner_thread_id + 1
            ids(abs_id) = abs_id
        !$omp end parallel

    !$omp end parallel

    print '(A, I0)', 'total threads = ', total_threads
    print *, ids(1:total_threads)

end program multilevel
