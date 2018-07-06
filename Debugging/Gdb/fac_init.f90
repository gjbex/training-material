program fac_init
    implicit none
    integer :: i
    do i = 0, 5
        print '(A, I1, A, I6)', 'factorial(', i, ') =', factorial(i)
    end do
    
contains

    function factorial(n) result(fact)
        implicit none
        integer, intent(in) :: n
        integer :: fact
        integer :: fac = 1
        integer :: i
        do i = 2, n
            fac = fac*i
        end do
        fact = fac
    end function factorial

end program fac_init
