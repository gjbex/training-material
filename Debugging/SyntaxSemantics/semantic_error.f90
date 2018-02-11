program semantic_error
    implicit none
    integer :: i
    do i = 0, 3
        print '(2I5)', i, fac(i)
    end do
contains

    integer function fac(n)
        implicit none
        integer, intent(in) :: n
        integer :: i
        fac = 1
        do i = 0, n
            fac = fac*i
        end do
    end function fac

end program semantic_error
