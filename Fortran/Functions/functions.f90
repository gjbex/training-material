program functions
    implicit none
    abstract interface
        function math_func(x)
            double precision, intent(in) :: x
            double precision :: math_func
        end function math_func
    end interface
    procedure(math_func) :: f1, f2, f3
    real(kind=4) :: t, time_func
    t = time_func(f1)
    print "(A10, F16.6, A1)", "x**2", t, "s"
    t = time_func(f2)
    print "(A10, F16.6)", "sqrt(x)", t
    t = time_func(f3)
    print "(A10, F16.6)", "exp(x)", t

end program functions

function f1(x) result(r)
    implicit none
    double precision, intent(in) :: x
    double precision :: r
    r = x**2
end function f1

function f2(x) result(r)
    implicit none
    double precision, intent(in) :: x
    double precision :: r
    r = sqrt(x)
end function f2

function f3(x) result(r)
    implicit none
    double precision, intent(in) :: x
    double precision :: r
    r = exp(x)
end function f3

function time_func(math_func) result(t)
    implicit none
    interface
        function math_func(x)
            double precision, intent(in) :: x
            double precision :: math_func
        end function
    end interface
    real(kind=4) :: t
    real(kind=4) :: t_start, t_end
    double precision, parameter :: x_delta = 1.0D-09, &
                                   x_min   = 1.0D-14, &
                                   x_max   = 1.0D00
    double precision :: x, total
    x = x_min
    total = 0.0D00
    call cpu_time(t_start)
    do while (x <= x_max)
        total = total + math_func(x)
        x = x + x_delta
    end do
    call cpu_time(t_end)
    print *, total
    t = t_end - t_start
end function time_func
