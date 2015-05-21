program do_test
    implicit none
    integer :: i

    do i = 0, 10, 2
        print *, i
    end do
    print '(A, I0)', 'value of do-loop index after block: ', i

end program do_test
