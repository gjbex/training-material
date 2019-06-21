module array_utils
    implicit none

    public :: sum_array

contains

    function sum_array(a) result(s)
        implicit none
        real(kind=8), intent(in), dimension(:) :: a
        real(kind=8) :: s
        integer :: i, n
        n = size(a)
        s = 0.0D00
        do i = 1, n
            s = s + a(i)
        end do
    end function sum_array

end module array_utils

