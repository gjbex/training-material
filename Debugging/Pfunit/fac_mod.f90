module fac_mod
    use, intrinsic :: iso_fortran_env, only : i32 => INT32
    implicit none

    public :: fac

contains

    function fac(n) result(r)
        implicit none
        integer(kind=i32), intent(in) :: n
        integer(kind=i32) :: r
        integer :: i
        r = 1_i32
        do i = 2, n
            r = r*i
        end do
    end function fac

end module fac_mod
