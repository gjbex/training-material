program internals_test
    use internals_mod
    implicit none
    integer, parameter :: n = 5
    integer :: i
    real, parameter :: x_min = 0.0, x_delta = 0.1
    real :: x
    real, dimension(n) :: values

    call compute()
    print "(5F7.3)", values
    call compute_more(n, x)
    print "(A, F15.7)", 'program x = ', x

contains

    subroutine compute()
        implicit none
        real :: x

        x = x_min
        do i = 1, n
            values(i) = cos(2.0*3.14*x)
            x = x + x_delta
        end do
    end subroutine compute
            
end program internals_test
