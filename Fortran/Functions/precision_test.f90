program precision_test
    use, intrinsic :: iso_fortran_env, only : sp => REAL32, dp => REAL64
    implicit none
    integer, parameter :: rp = sp
    integer, parameter :: x_dim = 1000, nr_outer = 10
    real(kind=rp), dimension(x_dim) :: x1, x2, x3
    integer :: i, j, k, p
    real(kind=sp) :: t_start, t_end
    real(kind=rp) :: x, y, x_l1, x_l2, x_l3, total, t1, t2, t3
    character(len=25) :: r_fmt_str = "(A, A, F10.3, A, E15.7)", &
                         c_fmt_str = "('# ', A)", &
                         comp_str

    do i = 1, x_dim
        call random_number(x)
        x1(i) = x
        call random_number(x)
        x2(i) = x
        call random_number(x)
        x3(i) = x
    end do

    comp_str = "x + y"
    print c_fmt_str, trim(comp_str)
    total = 0.0_rp
    call cpu_time(t_start)
    do p = 1, nr_outer
        t1 = 0.0_rp
        x_l1 = p*0.001_rp
        do i = 1, x_dim
            t2 = 0.0_rp
            x_l2 = x_l1 + x1(i)
            do j = 1, x_dim
                t3 = 0.0_rp
                x_l3 = x_l2 + x2(j)
                do k = 1, x_dim
                    x = x_l3 + x3(k)
                    y = x2(k)
                    t3 = t3 + x + y
                end do
                t2 = t2 + t3
            end do
            t1 = t1 + t2
        end do
        total = total + t1
    end do
    call cpu_time(t_end)
    print r_fmt_str, trim(comp_str), ",", t_end - t_start, ",", total

    comp_str = "x*y"
    print c_fmt_str, trim(comp_str)
    total = 0.0_rp
    call cpu_time(t_start)
    do p = 1, nr_outer
        t1 = 0.0_rp
        x_l1 = p*0.001_rp
        do i = 1, x_dim
            t2 = 0.0_rp
            x_l2 = x_l1 + x1(i)
            do j = 1, x_dim
                t3 = 0.0_rp
                x_l3 = x_l2 + x2(j)
                do k = 1, x_dim
                    x = x_l3 + x3(k)
                    y = x2(k)
                    t3 = t3 + x*y
                end do
                t2 = t2 + t3
            end do
            t1 = t1 + t2
        end do
        total = total + t1
    end do
    call cpu_time(t_end)
    print r_fmt_str, trim(comp_str), ",", t_end - t_start, ",", total

    comp_str = "x*y + x"
    print c_fmt_str, trim(comp_str)
    total = 0.0_rp
    call cpu_time(t_start)
    do p = 1, nr_outer
        t1 = 0.0_rp
        x_l1 = p*0.001_rp
        do i = 1, x_dim
            t2 = 0.0_rp
            x_l2 = x_l1 + x1(i)
            do j = 1, x_dim
                t3 = 0.0_rp
                x_l3 = x_l2 + x2(j)
                do k = 1, x_dim
                    x = x_l3 + x3(k)
                    y = x2(k)
                    t3 = t3 + x*y + x
                end do
                t2 = t2 + t3
            end do
            t1 = t1 + t2
        end do
        total = total + t1
    end do
    call cpu_time(t_end)
    print r_fmt_str, trim(comp_str), ",", t_end - t_start, ",", total

    comp_str = "x/y"
    print c_fmt_str, trim(comp_str)
    total = 0.0_rp
    call cpu_time(t_start)
    do p = 1, nr_outer
        t1 = 0.0_rp
        x_l1 = p*0.001_rp
        do i = 1, x_dim
            t2 = 0.0_rp
            x_l2 = x_l1 + x1(i)
            do j = 1, x_dim
                t3 = 0.0_rp
                x_l3 = x_l2 + x2(j)
                do k = 1, x_dim
                    x = x_l3 + x3(k)
                    y = x2(k)
                    t3 = t3 + x/y
                end do
                t2 = t2 + t3
            end do
            t1 = t1 + t2
        end do
        total = total + t1
    end do
    call cpu_time(t_end)
    print r_fmt_str, trim(comp_str), ",", t_end - t_start, ",", total

    comp_str = "x**y"
    print c_fmt_str, trim(comp_str)
    total = 0.0_rp
    call cpu_time(t_start)
    do p = 1, nr_outer
        t1 = 0.0_rp
        x_l1 = p*0.001_rp
        do i = 1, x_dim
            t2 = 0.0_rp
            x_l2 = x_l1 + x1(i)
            do j = 1, x_dim
                t3 = 0.0_rp
                x_l3 = x_l2 + x2(j)
                do k = 1, x_dim
                    x = x_l3 + x3(k)
                    y = x2(k)
                    t3 = t3 + x**y
                end do
                t2 = t2 + t3
            end do
            t1 = t1 + t2
        end do
        total = total + t1
    end do
    call cpu_time(t_end)
    print r_fmt_str, trim(comp_str), ",", t_end - t_start, ",", total

    comp_str = "sqrt(x)"
    print c_fmt_str, trim(comp_str)
    total = 0.0_rp
    call cpu_time(t_start)
    do p = 1, nr_outer
        t1 = 0.0_rp
        x_l1 = p*0.001_rp
        do i = 1, x_dim
            t2 = 0.0_rp
            x_l2 = x_l1 + x1(i)
            do j = 1, x_dim
                t3 = 0.0_rp
                x_l3 = x_l2 + x2(j)
                do k = 1, x_dim
                    x = x_l3 + x3(k)
                    t3 = t3 + sqrt(x)
                end do
                t2 = t2 + t3
            end do
            t1 = t1 + t2
        end do
        total = total + t1
    end do
    call cpu_time(t_end)
    print r_fmt_str, trim(comp_str), ",", t_end - t_start, ",", total

    comp_str = "exp(x)"
    print c_fmt_str, trim(comp_str)
    total = 0.0_rp
    call cpu_time(t_start)
    do p = 1, nr_outer
        t1 = 0.0_rp
        x_l1 = p*0.001_rp
        do i = 1, x_dim
            t2 = 0.0_rp
            x_l2 = x_l1 + x1(i)
            do j = 1, x_dim
                t3 = 0.0_rp
                x_l3 = x_l2 + x2(j)
                do k = 1, x_dim
                    x = x_l3 + x3(k)
                    t3 = t3 + exp(x)
                end do
                t2 = t2 + t3
            end do
            t1 = t1 + t2
        end do
        total = total + t1
    end do
    call cpu_time(t_end)
    print r_fmt_str, trim(comp_str), ",", t_end - t_start, ",", total

    comp_str = "log(x)"
    print c_fmt_str, trim(comp_str)
    total = 0.0_rp
    call cpu_time(t_start)
    do p = 1, nr_outer
        t1 = 0.0_rp
        x_l1 = p*0.001_rp
        do i = 1, x_dim
            t2 = 0.0_rp
            x_l2 = x_l1 + x1(i)
            do j = 1, x_dim
                t3 = 0.0_rp
                x_l3 = x_l2 + x2(j)
                do k = 1, x_dim
                    x = x_l3 + x3(k)
                    t3 = t3 + log(x)
                end do
                t2 = t2 + t3
            end do
            t1 = t1 + t2
        end do
        total = total + t1
    end do
    call cpu_time(t_end)
    print r_fmt_str, trim(comp_str), ",", t_end - t_start, ",", total

    comp_str = "erf(x)"
    print c_fmt_str, trim(comp_str)
    total = 0.0_rp
    call cpu_time(t_start)
    do p = 1, nr_outer
        t1 = 0.0_rp
        x_l1 = p*0.001_rp
        do i = 1, x_dim
            t2 = 0.0_rp
            x_l2 = x_l1 + x1(i)
            do j = 1, x_dim
                t3 = 0.0_rp
                x_l3 = x_l2 + x2(j)
                do k = 1, x_dim
                    x = x_l3 + x3(k)
                    t3 = t3 + erf(x)
                end do
                t2 = t2 + t3
            end do
            t1 = t1 + t2
        end do
        total = total + t1
    end do
    call cpu_time(t_end)
    print r_fmt_str, trim(comp_str), ",", t_end - t_start, ",", total

    comp_str = "random_number(x)"
    print c_fmt_str, trim(comp_str)
    total = 0.0_rp
    call cpu_time(t_start)
    do p = 1, nr_outer
        t1 = 0.0_rp
        x_l1 = p*0.001_rp
        do i = 1, x_dim
            t2 = 0.0_rp
            x_l2 = x_l1 + x1(i)
            do j = 1, x_dim
                t3 = 0.0_rp
                x_l3 = x_l2 + x2(j)
                do k = 1, x_dim
                    call random_number(x)
                    t3 = t3 + x
                end do
                t2 = t2 + t3
            end do
            t1 = t1 + t2
        end do
        total = total + t1
    end do
    call cpu_time(t_end)
    print r_fmt_str, trim(comp_str), ",", t_end - t_start, ",", total

end program precision_test
