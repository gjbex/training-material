program block_test
    implicit none
    integer :: i

    do i = 1, 10
        block
            integer :: j
            real :: frac
            j = i*3
            print *, i, j
            frac = 1.0/i
            print *, i, frac
        end block
    end do
end program block_test
