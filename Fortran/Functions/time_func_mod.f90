module time_func_mod
    use, intrinsic :: iso_fortran_env, only : sp => REAL32, dp => REAL64
    use math_func_interface
    implicit none

    type, public :: result_record
        real(kind=dp) :: result
        real(kind=sp) :: time
    end type result_record
    public :: time_func, time_func_unrolled

contains

    function time_func(f) result(r)
        implicit none
        procedure(math_func) :: f
        type(result_record) :: r
        real(kind=sp) :: t_start, t_end
        real(kind=dp), parameter :: x_delta = 1.0e-09_dp, &
                                    x_min   = 1.0e-14_dp, &
                                    x_max   = 1.0_dp
        real(kind=dp) :: x, total
        x = x_min
        total = 0.0_dp
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
        real(kind=sp) :: t_start, t_end
        real(kind=dp), parameter :: x_delta = 1.0e-09_dp, &
                                    x_min   = 1.0e-14_dp, &
                                    x_max   = 1.0_dp
        real(kind=dp) :: x1, x2, x3, x4, x_delta_unrolled, &
                         total1, total2, total3, total4
        x1 = x_min
        x2 = x1 + x_delta
        x3 = x2 + x_delta
        x4 = x3 + x_delta
        x_delta_unrolled = 4*x_delta
        total1 = 0.0_dp
        total2 = 0.0_dp
        total3 = 0.0_dp
        total4 = 0.0_dp
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
