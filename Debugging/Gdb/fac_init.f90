program fac_init
    use fac_mod
    implicit none
    integer :: i
    do i = 0, 5
        print '(A, I1, A, I6)', 'factorial(', i, ') =', factorial(i)
    end do
end program fac_init
