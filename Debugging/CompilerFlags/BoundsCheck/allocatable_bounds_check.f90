program array_bounds_check
    implicit none
    integer, parameter :: n = 5
    integer, allocatable, dimension(:) :: x
    integer :: i
    call init_array(n , x)
    do i = 1, n + 1
        print '(I2, I3)', x(i)
    end do

contains

    subroutine init_array(n, x)
        implicit none
        integer, intent(in) :: n
        integer, allocatable, dimension(:), intent(out) :: x
        integer :: status, i
        allocate(x(n), stat=status)
        if (status /= 0) then
            print '(A)', '### error: can not allocate'
            stop
        end if
        do i = 1, n
            x(i) = i**2
        end do
    end subroutine init_array

end program array_bounds_check
