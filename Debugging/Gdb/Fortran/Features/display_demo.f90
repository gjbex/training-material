program display_demo
    implicit none
    integer, parameter :: max_pow = 10
    integer :: i
    real :: total

    total = 0.0
    do i = 0, max_pow
        total = total + 10.0**i
    end do

    print '(ES15.3)', total

end program display_demo
