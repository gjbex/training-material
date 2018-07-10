module fac_mod
    use, intrinsic :: iso_fortran_env, only : i32 => INT32
    implicit none

    public :: fac

contains

    integer(kind=i32) function fac(n)
        implicit none
        integer(kind=i32), intent(in) :: n
        integer(kind=i32) :: r = 1_i32
        integer :: i
        do i = 2, n
            r = r*i
        end do
        fac = r
    end function fac

end module fac_mod
