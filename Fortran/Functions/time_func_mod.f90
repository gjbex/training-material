module time_func_mod
    use, intrinsic :: iso_fortran_env
    use math_func_interface
    implicit none

    type, public :: result_record
        real(kind=REAL64) :: result
        real(kind=REAL32) :: time
    end type result_record
    public :: time_func, time_func_unrolled

contains

    function time_func(f) result(r)
        implicit none
        procedure(math_func) :: f
        type(result_record) :: r
        real(kind=REAL32) :: t_start, t_end
        real(kind=REAL64), parameter :: x_delta = 1.0D-09, &
                                       x_min   = 1.0D-14, &
                                       x_max   = 1.0D00
        real(kind=REAL64) :: x, total
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

    function time_func_unrolled(f) result(r)
        implicit none
        procedure(math_func) :: f
        type(result_record) :: r
        real(kind=REAL32) :: t_start, t_end
        real(kind=REAL64), parameter :: x_delta = 1.0D-09, &
                                       x_min   = 1.0D-14, &
                                       x_max   = 1.0D00
        real(kind=REAL64) :: x1, x2, x3, x4, x_delta_unrolled, &
                            total1, total2, total3, total4
        x1 = x_min
        x2 = x1 + x_delta
        x3 = x2 + x_delta
        x4 = x3 + x_delta
        x_delta_unrolled = 4*x_delta
        total1 = 0.0D00
        total2 = 0.0D00
        total3 = 0.0D00
        total4 = 0.0D00
        call cpu_time(t_start)
        do while (x4 <= x_max)
            total1 = total1 + f(x1)
            x1 = x1 + x_delta_unrolled
            total2 = total2 + f(x2)
            x2 = x2 + x_delta_unrolled
            total3 = total3 + f(x3)
            x3 = x3 + x_delta_unrolled
            total4 = total4 + f(x4)
            x4 = x4 + x_delta_unrolled
        end do
        call cpu_time(t_end)
        r%result = total1 + total2 + total3 + total4
        r%time = t_end - t_start
    end function time_func_unrolled

end module time_func_mod

