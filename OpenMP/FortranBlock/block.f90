program block
      use :: omp_lib
      implicit none
      !$omp parallel
      block
          integer :: thread_num, num_threads
          thread_num = omp_get_thread_num()
          num_threads = omp_get_num_threads()
          print '("hello from ", I0, " out of ", I0)', thread_num, num_threads
      end block
      !$omp end parallel
end program block
