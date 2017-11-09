program uninitialized_variable
    implicit none
    integer, parameter :: n = 5
    integer :: i
    do i = 1, n
        print '(A, F10.3)', 'sum = ', compute_sum(n)
    end do

contains

    function compute_sum(n) result(r)
        implicit none
        integer, intent(in) :: n
        real :: r, sum, x
        integer :: i
        do i = 1, n
            call random_number(x)
            sum = sum + x
        end do
        r = sum/n
    end function compute_sum

end program uninitialized_variable
