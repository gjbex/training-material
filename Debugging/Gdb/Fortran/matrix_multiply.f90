
program main

  implicit none

  integer, parameter :: sp = selected_real_kind(6)  
  integer, parameter :: dp = selected_real_kind(15)
  integer, parameter :: n = 650, m = 700, p = 750
  real(kind=dp) :: a(n, m), b(m, p), c(n, p)
  real(kind=dp) :: val, err
  real :: tic, toc, dt
 
  integer :: i, j, k

  call random_number(a)
  call random_number(b)

  call cpu_time(tic)
  do i = 1, n
     do j = 1, p
        val = 0d0
        do k = 1, m
           val = val + a(i, k) * b(k, j)
        enddo
        c(i, j) = val
     enddo
  enddo
  call cpu_time(toc)
  dt = toc - tic

  err = maxval(abs(matmul(a, b) - c))
  print '(a, 1pes23.16, a, f8.4)', 'max error occured = ', err, &
        '; dt [sec] = ', toc - tic

end program main
