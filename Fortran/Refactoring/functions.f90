real(kind=sp) function computationally_heavy(i)
    implicit none
    integer, intent(in) :: i
    real(kind=sp) :: x
    x = 2.0_sp*real(i, kind=sp)/m
    computationally_heavy = erf(x)
end function computationally_heavy

real(kind=sp) function whatever(j)
    implicit none
    integer, intent(in) :: j
    real(kind=sp) :: x
    x = 2.0_sp*real(j, kind=sp)/n
    whatever = sqrt(x)
end function whatever

real(kind=sp) function row_func(j)
    implicit none
    integer, intent(in) :: j
    real(kind=sp) :: x
    x = 2.0*real(j, kind=sp)/n
    row_func = exp(-x)
end function row_func

