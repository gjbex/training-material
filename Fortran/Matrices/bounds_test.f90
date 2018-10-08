program bounds_test
    implicit none
    integer, dimension(-2:2) :: values = [ 1, 2, 3, 4, 5 ]

    call print_array(values)

contains

    subroutine print_array(values)
        implicit none
        integer, dimension(:), intent(in) :: values
        integer :: i

        do i = 1, size(values)
            print '(I0)', values(i)
        end do
    end subroutine

end program bounds_test
