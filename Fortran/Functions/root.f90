program root
    use, intrinsic :: iso_fortran_env, only : dp => REAL64, &
                                              error_unit
    implicit none

    interface
        function func_type(x) result(f)
            use, intrinsic :: iso_fortran_env, only : dp => REAL64
            implicit none
            real(kind=dp), intent(in) :: x
            real(kind=dp) :: f
        end function func_type
    end interface

    real(kind=dp) :: a, b, eps, x0
    integer :: istat, steps

! deal with command line arguments
    call init(a, b, eps)

! compute zero
    x0 = find_root(target_func, a, b, eps, nr_steps=steps)
    print '(I12, E25.15)', steps, x0

contains

    function find_root(f, a, b, eps, nr_steps, max_steps) result(x0)
        implicit none
        procedure(func_type) :: f
        real(kind=dp), value :: a, b
        real(kind=dp), intent(in) :: eps
        integer, optional, intent(out) :: nr_steps
        integer, optional, value :: max_steps
        real(kind=dp) :: x0
        real(kind=dp) :: m, fa, fb, fm
        integer :: steps
        if (.not. present(max_steps)) then
            max_steps = 10000000
        end if
        fa = f(a)
        fb = f(b)
        steps = 1
        do while (abs(a - b) > eps .and. steps < max_steps)
            m = (a + b)/2.0_dp
            fm = f(m)
            if (fa*fm < 0) then
                b = m
                fb = fm
            else
                a = m
                fa = fm
            end if
            steps = steps + 1
        end do
        if (steps > max_steps) then
            write (unit=error_unit, fmt='(A)') &
                '#error: maximum number of steps exceeded'
            stop
        end if
        x0 = (a + b)/2.0_dp
        if (present(nr_steps)) nr_steps = steps
    end function find_root

    function target_func(x) result(f)
        implicit none
        real(kind=dp), intent(in) :: x
        real(kind=dp) :: f
        f = cos(x)
    end function target_func

    subroutine init(a, b, eps)
        implicit none
        real(kind=dp), intent(out) :: a, b, eps
        character(len=1024) :: buffer

        if (command_argument_count() /= 3) then
            write (unit=error_unit, fmt='(A)') &
                '#error: three arguments expected: a, b, and eps'
            stop
        end if
        call get_command_argument(1, buffer)
        read (buffer, '(E25.15)') a
        call get_command_argument(2, buffer)
        read (buffer, '(E25.15)') b
        call get_command_argument(3, buffer)
        print *, trim(buffer)
        read (buffer, fmt='(E25.15)') eps
    end subroutine init

end program root
