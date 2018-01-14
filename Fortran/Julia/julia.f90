program julia
    use, intrinsic :: iso_fortran_env, only : dp => REAL64
    implicit none

    integer, parameter :: default_steps = 100, &
                          exit_failure = 1, &
                          max_iters = 255
    complex(kind=dp), parameter :: c = (-0.62772_dp, -0.32193_dp)
    character(len=9), parameter :: file_name = 'julia.txt'
    real(kind=dp), parameter :: x1 = -1.8_dp, x2 = 1.8_dp, &
                                y1 = -1.8_dp, y2 = 1.8_dp
    integer :: steps, status
    real(kind=dp), dimension(:), allocatable :: x_coords, y_coords
    complex(kind=dp), dimension(:, :), allocatable :: z_vals
    integer, dimension(:, :), allocatable :: nr_iters
    character(len=80) :: buffer

! initialize steps, either from the command line argument or to default
    if (command_argument_count() > 0) then
        call get_command_argument(1, buffer)
        read (buffer, '(I10)') steps
    else
        steps = default_steps
    end if

! allocate and initialize coordinates
    call init_coords(x_coords, x1, x2, steps)
    call init_coords(y_coords, y1, y2, steps)

! allocate and initialize complex plane
    call init_z_vals(z_vals, x_coords, y_coords)

! allocate and initialize the array to hold the number of iterations
! for the points in the complex plane
    allocate(nr_iters(steps, steps), stat=status)
    if (status /= 0) then
        call report_error('can not allocate n')
    end if
    nr_iters = 0

! perform iterations
    call iterate_z_vals(z_vals, nr_iters, c, max_iters)

! print result
    call print_result(nr_iters, file_name)

contains

    subroutine init_coords(coords, lower, upper, steps)
        implicit none
        real(kind=dp), dimension(:), allocatable, intent(out) :: coords
        real(kind=dp), intent(in) :: lower, upper
        integer, intent(in) :: steps
        real(kind=dp) :: delta
        integer :: i, istat
        delta = (upper - lower)/steps
        allocate(coords(steps), stat=istat)
        if (istat /= 0) then
            call report_error('can not allocate coordinates')
        end if
        forall (i = 1:steps)
            coords(i) = lower + (i - 1)*delta
        end forall
    end subroutine init_coords

    subroutine init_z_vals(z_vals, x_coords, y_coords)
        implicit none
        complex(kind=dp), dimension(:, :), allocatable, &
                          intent(out) :: z_vals
        real(kind=dp), dimension(:), intent(in) :: x_coords, y_coords
        integer :: i, j, status
        allocate(z_vals(size(x_coords), size(y_coords)), stat=status)
        if (status /= 0) then
            call report_error('can not allocate z')
        end if
        forall (i = 1:size(x_coords), j = 1:size(y_coords))
            z_vals(i, j) = cmplx(x_coords(i), y_coords(j), &
                                 kind=kind(z_vals))
        end forall
    end subroutine init_z_vals

    subroutine iterate_z_vals(z_vals, nr_iters, c, max_iters)
        implicit none
        complex(kind=dp), dimension(:, :), intent(inout) :: z_vals
        integer, dimension(:, :), intent(inout) :: nr_iters
        complex(kind=dp), intent(in) :: c
        integer, intent(in) :: max_iters
        nr_iters = iterate_z_val(z_vals, c, max_iters)
    end subroutine iterate_z_vals

    elemental function iterate_z_val(z_val, c, max_iters) result(iters)
        implicit none
        complex(kind=dp), intent(in) :: z_val
        complex(kind=dp), intent(in) :: c
        integer, intent(in) :: max_iters
        complex(kind=dp) :: z
        integer :: iters
        z = z_val
        iters = 0
        do while (abs(z) < 2.0_dp .and. iters < max_iters)
            iters = iters + 1
            z = z*z + c
        end do
    end function iterate_z_val

    subroutine print_result(nr_iters, file_name)
        implicit none
        integer, dimension(:, :), intent(in) :: nr_iters
        character(len=*), intent(in) :: file_name
        integer, parameter :: file_unit = 14
        integer :: i, j, istat
        character(len=1024) :: msg
        character(len=128) :: row_fmt
        open(unit=file_unit, file=file_name, access='sequential', &
             action='write', status='replace', form='formatted', &
             iostat=istat, iomsg=msg)
        if (istat /= 0) then
            call report_error(msg)
        end if
        write (row_fmt, '(A, I0, A)') '(', size(nr_iters, 2), 'I4)'
        do i = 1, size(nr_iters,1)
            write (unit=file_unit, fmt=row_fmt, iostat=istat, iomsg=msg), &
                (int(255.0_dp*log(1.0_dp + nr_iters(i, j))/log(255.0_dp)), &
                 j = 1, size(nr_iters, 2))
            if (istat /= 0) then
                call report_error(msg)
            end if
        end do
        close(unit=file_unit, iostat=istat, iomsg=msg)
        if (istat /= 0) then
            call report_error(msg)
        end if
    end subroutine print_result

    subroutine report_error(msg)
        use, intrinsic :: iso_fortran_env, only : error_unit
        implicit none
        character(len=*), intent(in) :: msg
        write (unit=error_unit, fmt='("### error: ", A)') trim(msg)
        stop exit_failure
    end subroutine report_error

end program julia
