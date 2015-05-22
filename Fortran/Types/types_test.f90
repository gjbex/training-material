module math_funcs
    use iso_fortran_env, only : REAL32, REAL64
    implicit none

    private
    ! define the real kind to be used, either REAL31 or REAL64
#ifdef SINGLE_PREC
    integer, parameter, public :: rp = REAL32
#else
    integer, parameter, public :: rp = REAL64
#endif
    public :: linear

contains

    function linear(x) result(r)
        implicit none
        real(kind=rp), intent(in) :: x
        real(kind=rp) :: r
        r = 2.0_rp*x + 3.0_rp
    end function linear

end module math_funcs

program types_test
    use math_funcs, only : rp, linear
    implicit none
    real(kind=rp) :: x, y
    x = 1.0_rp
    y = 2.1_rp
    print *, x + y
    print *, linear(x)
    print *, kind(x)

end program types_test
