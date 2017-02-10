module system_class
use iso_fortran_env, only : REAL64, output_unit
use mpi_f08
use cl_params
implicit none

    type, public :: system_type
        private
        real(kind=REAL64), allocatable, dimension(:,:) :: temp, new_temp
        integer :: n_val
        integer :: upper, right, lower, left, rank
        type(MPI_Comm) :: comm
        type(MPI_Datatype) :: row_type, col_type
        real(kind=REAL64) :: diff_coeff_val
    contains
        procedure, public :: init        => init_system
        procedure, public :: init_mpi    => init_system_mpi
        procedure, public :: n           => get_n_system
        procedure, public :: diff_coeff  => get_diff_coeff_system
        procedure, public :: avg_temp    => avg_temp_system
        procedure, public :: apply_laser => apply_laser_system
        procedure, public :: step        => step_system
        procedure, public :: exchange_halos
        procedure, public :: delete      => delete_system
        procedure, public :: delete_mpi  => delete_system_mpi
        procedure, public :: show        => show_system
    end type system_type

private :: init_system, apply_laser_system, step_system, delete_system, &
           show_system, get_n_system, get_diff_coeff_system, &
           avg_temp_system, init_system_mpi

contains

    subroutine init_system(this, params)
        implicit none
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
        this%new_temp = 0.0_REAL64
    end subroutine init_system

    subroutine init_system_mpi(this, comm)
        implicit none
        class(system_type), intent(inout) :: this
        type(MPI_Comm), intent(in) :: comm
        this%comm = comm
        call MPI_Comm_rank(comm, this%rank)
        call MPI_Cart_shift(comm, 0, 1, this%upper, this%lower)
        call MPI_Cart_shift(comm, 1, 1, this%left, this%right)
        call MPI_Type_vector(this%n_val, 1, this%n_val - 2, &
                             MPI_DOUBLE_PRECISION, this%row_type)
        call MPI_Type_commit(this%row_type)
        call MPI_Type_contiguous(this%n_val - 1, MPI_DOUBLE_PRECISION, &
                                 this%col_type)
        call MPI_Type_commit(this%col_type)
    end subroutine init_system_mpi

    pure integer function get_n_system(this)
        implicit none
        class(system_type), intent(in) :: this
        get_n_system = this%n_val
    end function get_n_system

    real(kind=REAL64) function get_diff_coeff_system(this)
        implicit none
        class(system_type) :: this
        get_diff_coeff_system = this%diff_coeff_val
    end function get_diff_coeff_system

    subroutine apply_laser_system(this, params)
        implicit none
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
    end subroutine apply_laser_system

    subroutine exchange_halos(this)
        implicit none
        class(system_type), intent(inout) :: this
        type(MPI_Request), dimension(4) ::request
        type(MPI_Status), dimension(4) :: status
        integer :: halo_tag = 11
        call MPI_Isend(this%temp(2, 2), 1, this%row_type, &
                       this%upper, halo_tag, &
                       this%comm, request(1))
        call MPI_Isend(this%temp(this%n_val - 1, 2), 1, this%row_type, &
                       this%lower, halo_tag, &
                       this%comm, request(2))
        call MPI_Isend(this%temp(2, 2), 1, this%col_type, &
                       this%left, halo_tag, &
                       this%comm, request(3))
        call MPI_Isend(this%temp(2, this%n_val - 1), 1, this%col_type, &
                       this%right, halo_tag, &
                       this%comm, request(4))
        call MPI_recv(this%temp(1, 2), 1, this%row_type, &
                      this%upper, halo_tag, &
                      this%comm, status(1))
        call MPI_recv(this%temp(this%n_val, 2), 1, this%row_type, &
                      this%lower, halo_tag, &
                      this%comm, status(2))
        call MPI_recv(this%temp(2, 1), 1, this%col_type, &
                      this%left, halo_tag, &
                      this%comm, status(3))
        call MPI_recv(this%temp(2, this%n_val), 1, this%col_type, &
                      this%right, halo_tag, &
                      this%comm, status(4))
        call MPI_Waitall(4, request, status)
    end subroutine exchange_halos

    real(kind=REAL64) function avg_temp_system(this)
        implicit none
        class(system_type), intent(in) :: this
        avg_temp_system = sum(this%temp)/(this%n_val*this%n_val)
    end function avg_temp_system

    subroutine step_system(this)
        implicit none
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
    end subroutine step_system

    subroutine delete_system(this)
        implicit none
        class(system_type), intent(inout) :: this
        deallocate(this%temp)
        deallocate(this%new_temp)
    end subroutine delete_system

    subroutine delete_system_mpi(this)
        implicit none
        class(system_type), intent(inout) :: this
        call MPI_Type_free(this%row_type)
        call MPI_Type_free(this%col_type)
    end subroutine delete_system_mpi

    subroutine show_system(this, time, unit)
        implicit none
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
        write (o_unit, '(A, I5)') 'rank = ', this%rank
        write (rowfmt, '(A,I4,A)') '(', this%n_val, '(F7.3))'
        do row = 1, this%n_val
            write (o_unit, rowfmt) this%temp(row, :)
        end do
    end subroutine show_system

end module system_class
