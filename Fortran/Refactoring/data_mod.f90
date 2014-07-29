module data_mod
    use, intrinsic :: iso_fortran_env
    implicit none
    private
    integer, public, parameter :: sp = REAL32
    type, public :: data_type
        real(kind=sp), pointer, dimension(:, :) :: data => null()
        integer :: nr_rows = 0, nr_cols = 0
    contains
        procedure, public :: allocate_data
        procedure, public :: deallocate_data
        procedure, public :: dshape
        generic, public :: get => get_element, get_row
        procedure, public :: get_element
        procedure, public :: get_row
        generic, public :: set => set_element, set_row
        procedure, public :: set_element
        procedure, public :: set_row
    end type data_type

contains

    subroutine allocate_data(this, m, n)
        implicit none
        class(data_type), intent(inout) :: this
        integer, intent(in) :: m, n
        integer :: status
        this%nr_rows = m
        this%nr_cols = n
        allocate(this%data(n, m), stat=status)
        if (status /= 0) then
            write (unit=error_unit, fmt="(A)") "# error: allocate failed"
            stop
        end if
    end subroutine allocate_data

    subroutine deallocate_data(this)
        implicit none
        class(data_type), intent(inout) :: this
        deallocate(this%data)
    end subroutine deallocate_data

    function dshape(this) result(dims)
        implicit none
        class(data_type), intent(in) :: this
        integer, dimension(2) :: dims
        integer :: tmp
        dims = shape(this%data)
        tmp = dims(1)
        dims(1) = dims(2)
        dims(2) = tmp
    end function dshape

    function get_element(this, i, j) result(value)
        implicit none
        class(data_type), intent(in) :: this
        integer, intent(in) :: i, j
        real(kind=sp) :: value
        value = this%data(j, i)
    end function get_element

    function get_row(this, i) result(row)
        implicit none
        class(data_type), intent(in) :: this
        integer, intent(in) :: i
        real(kind=sp), dimension(this%nr_cols) :: row
        row = this%data(:, i)
    end function get_row

    subroutine set_element(this, i, j, value)
        implicit none
        class(data_type), intent(inout) :: this
        integer, intent(in) :: i, j
        real(kind=sp), intent(in) :: value
        this%data(j, i) = value
    end subroutine set_element

    subroutine set_row(this, i, row)
        implicit none
        class(data_type), intent(inout) :: this
        integer, intent(in) :: i
        real(kind=sp), dimension(:), intent(in) :: row
        this%data(:, i) = row
    end subroutine set_row

end module data_mod
