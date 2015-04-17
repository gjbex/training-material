program block_test
    implicit none
    integer :: i

    do i = 1, 10
        block
            integer :: j
            j = i*3
            print *, i, j
        end block
    end do
end program block_test
