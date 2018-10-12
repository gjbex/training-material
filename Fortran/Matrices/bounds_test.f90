program bounds_test
    implicit none
    integer, dimension(-2:2) :: values = [ 1, 2, 3, 4, 5 ]

    print '("program: ", I0, " -> ", I0)', &
        lbound(values), ubound(values)
    call print_array(values)
    print '(I0)', values

contains

    subroutine print_array(values)
        implicit none
        integer, dimension(:), intent(in) :: values
        integer :: i

        print '("subroutine: ", I0, " -> ", I0)', &
            lbound(values), ubound(values)
        do i = 1, size(values)
            print '(I0)', values(i)
        end do
    end subroutine

end program bounds_test
