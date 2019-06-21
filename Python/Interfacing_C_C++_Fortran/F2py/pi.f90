function compute_pi(n) result(pi)
    integer, intent(in) :: n
    real(kind=8) :: pi, x, y
    integer :: i

    do i = 1, n
        call random_number(x)
        call random_number(y)
        if (x**2.0D00 + y**2.0D00 <= 1.0D00) then
            pi = pi + 1.0D00
        end if
    end do
    pi = 4.0D00*pi/n
end function compute_pi

