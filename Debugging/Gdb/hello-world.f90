program hello_world
     
  integer*4 nthreads, tid, &
       &    OMP_GET_NUM_THREADS, OMP_GET_THREAD_NUM
  
  ! Fork a team of threads giving them their own copies of variables
  !$OMP PARALLEL PRIVATE(nthreads, tid)

  ! Obtain thread number
  tid = OMP_GET_THREAD_NUM()
  print *, 'Hello World from thread = ', tid

  ! Only master thread does this
  if (tid == 0) then
     nthreads = OMP_GET_NUM_THREADS()
     print *, 'Number of threads = ', nthreads
  end if

  ! All threads join master thread and disband
  !$OMP END PARALLEL

end program hello_world
