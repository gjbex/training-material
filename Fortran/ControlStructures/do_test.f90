program do_test
    implicit none
    integer, parameter :: sp = selected_real_kind(p=6, r=30)
    integer :: i

    do i = 0, 10, 2
        print *, i
    end do
    print *, i

end program do_test
