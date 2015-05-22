module random_mod
    use, intrinsic :: iso_fortran_env, only : sp => REAL32, dp => REAL64
    implicit none

    private
    public :: random_normal_number

contains

    subroutine random_normal_number(r)
        implicit none
        real(kind=dp), intent(out) :: r
        real(kind=dp), parameter :: pi = acos(-1.0_dp)
        real(kind=dp) :: x1, x2, r_temp
        real(kind=dp), save :: next_r
        logical, save :: prev_ok = .false.
        
        if (prev_ok) then
            prev_ok = .false.
            r = next_r
        else
            prev_ok = .true.
            call random_number(x1)
            call random_number(x2)
            r_temp = sqrt(-2.0_dp*log(x1))
            next_r = r_temp*cos(2.0_dp*pi*x2)
            r = r_temp*sin(2.0_dp*pi*x2)
        end if
    end subroutine random_normal_number

end module random_mod
