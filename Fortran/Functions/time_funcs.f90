program time_funcs
    use math_func_mod
    implicit none
    real(kind=4) :: t, time_func
    integer :: i
    call setup()
    do i = 1, size(functions)
        t = time_func(functions(i)%f)
        print "(A10, F16.6, A1)", functions(i)%name, t, "s"
    end do

end program time_funcs

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

