module data_mod
    use, intrinsic :: iso_fortran_env
    implicit none
    private
    integer, public, parameter :: sp = REAL32
    type, public :: data_type
        real(kind=sp), pointer, dimension(:, :) :: data => null()
    contains
        procedure, public :: allocate_data
        procedure, public :: deallocate_data
        procedure, public :: get
        procedure, public :: set
    end type data_type

contains

    subroutine allocate_data(this, m, n)
        implicit none
        class(data_type), intent(inout) :: this
        integer, intent(in) :: m, n
        integer :: status
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

    real(kind=sp) function get(this, i, j)
        implicit none
        class(data_type), intent(in) :: this
        integer, intent(in) :: i, j
        get = this%data(j, i)
    end function get

    subroutine set(this, i, j, value)
        implicit none
        class(data_type), intent(inout) :: this
        integer, intent(in) :: i, j
        real(kind=sp), intent(in) :: value
        this%data(j, i) = value
    end subroutine set

end module data_mod
