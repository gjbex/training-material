module system_class
use iso_fortran_env, only : REAL64, output_unit
use cl_params
implicit none

    type, public :: system_type
        private
        real(kind=REAL64), allocatable, dimension(:,:) :: temp, new_temp
        integer :: n_val
        real(kind=REAL64) :: diff_coeff_val
    contains
        procedure, public :: init        => init_system
        procedure, public :: n           => get_n_system
        procedure, public :: diff_coeff  => get_diff_coeff_system
        procedure, public :: avg_temp    => avg_temp_system
        procedure, public :: apply_laser => apply_laser_system
        procedure, public :: step        => step_system
        procedure, public :: delete      => delete_system
        procedure, public :: show        => show_system
    end type system_type

private :: init_system, apply_laser_system, step_system, delete_system, &
           show_system, get_n_system, get_diff_coeff_system, avg_temp_system

contains

    subroutine init_system(this, params)
        class(system_type), intent(out) :: this
        type(params_type), intent(in) :: params
        integer :: istat

        this%n_val = params%n
        this%diff_coeff_val = params%diff_coeff
        allocate(this%temp(this%n(), this%n()), stat=istat)
        if (istat /= 0) then
            write (error_unit, '(A)') '### error: can not allocate temp'
            stop
        end if
        this%temp = params%init_temp
        allocate(this%new_temp(this%n(), this%n()), stat=istat)
        if (istat /= 0) then
            write (error_unit, '(A)') '### error: can not allocate new_temp'
            stop
        end if
        this%new_temp = 0.0D00
        return
    end subroutine init_system

    integer function get_n_system(this)
        class(system_type) :: this
        get_n_system = this%n_val
    end function get_n_system

    real(kind=REAL64) function get_diff_coeff_system(this)
        class(system_type) :: this
        get_diff_coeff_system = this%diff_coeff_val
    end function get_diff_coeff_system

    subroutine apply_laser_system(this, params)
        class(system_type), intent(inout) :: this
        type(params_type), intent(in) :: params
        integer :: spot_nr, offset, x_spot, y_spot, x, y
        real(kind=REAL64) :: r, distance
        offset = int(params%spot_size)
        do spot_nr = 1, params%nr_spots
            call random_number(r)
            x_spot = offset + int(r*(this%n_val - 2*offset))
            call random_number(r)
            y_spot = offset + int(r*(this%n_val - 2*offset))
            call random_number(r)
            do x = max(1, x_spot - offset + 1), &
                   min(this%n_val, x_spot + offset - 1)
                do y = max(1, y_spot - offset + 1), &
                       min(this%n_val, y_spot + offset - 1)
                    distance = sqrt(dble((x - x_spot)**2 + (y - y_spot)**2)) 
                    if (distance <= params%spot_size) then
                        this%temp(x, y) = this%temp(x, y) + &
                                          r*params%max_spot_temp
                    end if
                end do
            end do
        end do
        return
    end subroutine apply_laser_system

    real(kind=REAL64) function avg_temp_system(this)
        class(system_type), intent(in) :: this
        avg_temp_system = sum(this%temp)/(this%n_val*this%n_val)
    end function avg_temp_system

    subroutine step_system(this)
        class(system_type), intent(inout) :: this
        integer :: i, j
        do i = 2, this%n_val - 1
            do j = 2, this%n_val - 1
                this%new_temp(i, j) =            &
                    (this%temp(i - 1, j) +       &
                     this%temp(i + 1, j) +       &
                     this%temp(i, j - 1) +       &
                     this%temp(i, j + 1))*0.25*this%diff_coeff_val
            end do
        end do
        this%temp = this%new_temp
        return
    end subroutine step_system

    subroutine delete_system(this)
        class(system_type), intent(inout) :: this
        deallocate(this%temp)
        deallocate(this%new_temp)
        return
    end subroutine delete_system

    subroutine show_system(this, time, unit)
        class(system_type), intent(in) :: this
        integer, intent(in), optional :: time, unit
        integer :: row, o_unit
        character(len=40) :: rowfmt
        if (present(unit)) then
            o_unit = unit
        else
            o_unit = output_unit
        end if
        if (present(time)) write (o_unit, '(A, I10)') 'time = ', time
        write (rowfmt, '(A,I4,A)') '(', this%n_val, '(F7.3))'
        do row = 1, this%n_val
            write (o_unit, rowfmt) this%temp(row, :)
        end do
        return
        end subroutine show_system

end module system_class

