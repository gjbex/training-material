program do_while_test
    REAL :: x

    x = 5.0
    do while (x > 0.0)
        print *, x
        x = x - 0.5
    end do

end program do_while_test
