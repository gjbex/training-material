program block_test
    implicit none
    integer :: i, j

    j = -10
    print '(A, I0)', 'global j: ', j
    do i = 1, 10
        block
            integer :: j
            real :: frac
            j = i*3
            print '(A, I0, A, I0)', 'local j for ', i, ' = ', j
            frac = 1.0/i
            print *, i, frac
        end block
    end do
    print '(A, I0)', 'global j: ', j
end program block_test
