program vectorization_test
    use, intrinsic :: iso_fortran_env, only : sp => REAL32, &
                                              dp => REAL64, &
                                              ip => INT64
    implicit none
    integer, parameter :: rp = dp
    integer(kind=ip), parameter :: nr_ops = 10000000000_ip
    real(kind=sp) :: t_start, t_end
    real(kind=rp), parameter :: x_delta = 1.0e-09_rp, &
                                x_min   = 1.0e-14_rp, &
                                x_max   = 1.0_rp
    real(kind=rp) :: x, y, total

    integer(kind=ip) :: i
    print "(A)", "# x + y"
    x = x_min
    y = x_max
    total = 0.0_rp
    call cpu_time(t_start)
    do i = 1, nr_ops
        total = total + x + y
        x = x + x_delta
        y = y - x_delta
    end do
    call cpu_time(t_end)
    print "(A, F10.3)", "time = ", t_end - t_start
    print "(A, E18.7)", "total value = ", total

    print "(A)", "# x*y + x"
    x = x_min
    y = x_max
    total = 0.0_rp
    call cpu_time(t_start)
    do i = 1, nr_ops
        total = total + x*y + x
        x = x + x_delta
        y = y - x_delta
    end do
    call cpu_time(t_end)
    print "(A, F10.3)", "time = ", t_end - t_start
    print "(A, E18.7)", "total value = ", total

    print "(A)", "# 2.13/x"
    x = x_min
    total = 0.0_rp
    call cpu_time(t_start)
    do i = 1, nr_ops
        total = total + 2.13_rp/x
        x = x + x_delta
    end do
    call cpu_time(t_end)
    print "(A, F10.3)", "time = ", t_end - t_start
    print "(A, E18.7)", "total value = ", total

    print "(A)", "# x**2.1"
    x = x_min
    total = 0.0_rp
    call cpu_time(t_start)
    do i = 1, nr_ops
        total = total + x**2.1_rp
        x = x + x_delta
    end do
    call cpu_time(t_end)
    print "(A, F10.3)", "time = ", t_end - t_start
    print "(A, E18.7)", "total value = ", total

    print "(A)", "# sqrt(x)"
    x = x_min
    total = 0.0_rp
    call cpu_time(t_start)
    do i = 1, nr_ops
        total = total + sqrt(x)
        x = x + x_delta
    end do
    call cpu_time(t_end)
    print "(A, F10.3)", "time = ", t_end - t_start
    print "(A, E18.7)", "total value = ", total

    print "(A)", "# exp(x)"
    x = x_min
    total = 0.0_rp
    call cpu_time(t_start)
    do i = 1, nr_ops
        total = total + exp(x)
        x = x + x_delta
    end do
    call cpu_time(t_end)
    print "(A, F10.3)", "time = ", t_end - t_start
    print "(A, E18.7)", "total value = ", total

    print "(A)", "# erf(x)"
    x = x_min
    total = 0.0_rp
    call cpu_time(t_start)
    do i = 1, nr_ops
        total = total + erf(x)
        x = x + x_delta
    end do
    call cpu_time(t_end)
    print "(A, F10.3)", "time = ", t_end - t_start
    print "(A, E18.7)", "total value = ", total

end program vectorization_test
