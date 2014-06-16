module time_func_mod
    use math_func_mod
    implicit none

    type, public :: result_record
        double precision :: result
        real(kind=4) :: time
    end type result_record

contains

    function time_func(f) result(r)
        implicit none
        procedure(math_func) :: f
        type(result_record) :: r
        real(kind=4) :: t_start, t_end
        double precision, parameter :: x_delta = 1.0D-09, &
                                       x_min   = 1.0D-14, &
                                       x_max   = 1.0D00
        double precision :: x, total
        x = x_min
        total = 0.0D00
        call cpu_time(t_start)
        do while (x <= x_max)
            total = total + f(x)
            x = x + x_delta
        end do
        call cpu_time(t_end)
        r%result = total
        r%time = t_end - t_start
    end function time_func

end module time_func_mod

