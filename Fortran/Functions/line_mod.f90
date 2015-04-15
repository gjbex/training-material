module line_mod
    use types_mod
    implicit none

    private
    public :: on_line, line

contains

    elemental function line(x) result(y)
        implicit none
        real(kind=sp), intent(in) :: x
        real(kind=sp) :: y
        y = 3.0 + 0.5*x
    end function line

    elemental function on_line(x, y) result(is_on_line)
        implicit none
        real(kind=sp), intent(in) :: x, y
        logical :: is_on_line
        real(kind=sp) :: y_exp
        y_exp = line(x)
        is_on_line = equal(y, y_exp)

    contains

        pure function equal(a, b) result(is_equal)
            implicit none
            real(kind=sp), intent(in) :: a, b
            logical :: is_equal
            is_equal = abs(a - b) < 1.0e-6
        end function equal

    end function on_line

end module line_mod
