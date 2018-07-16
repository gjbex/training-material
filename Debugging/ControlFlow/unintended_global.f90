program uninitialized_variable
    implicit none
    integer, parameter :: n = 5
    integer :: i
    do i = 1, n
        print '(A, F10.3)', 'sum = ', compute_sum(n)
    end do

contains

    function compute_sum(n) result(sum)
        implicit none
        integer, intent(in) :: n
        real :: sum, x
        sum = 0.0
        do i = 1, n
            call random_number(x)
            sum = sum + x
        end do
        sum = sum/n
    end function compute_sum

end program uninitialized_variable
