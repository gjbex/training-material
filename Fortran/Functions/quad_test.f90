program quad_test
    use types_mod, only : dp
    use quad_mod, only : quad
    implicit none
    real(kind=dp), parameter :: a = -1.0_dp, b = 1.0_dp

    print *, quad(f, a, b)

contains

    real(kind=dp) function f(x)
        implicit none
        real(Kind=dp), intent(in) :: x
        f = exp(x)
    end function f

end program quad_test
