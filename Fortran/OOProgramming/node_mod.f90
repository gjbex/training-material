module node_mod
    use, intrinsic :: iso_fortran_env
    implicit none

    private

    type, public :: node_type
        private
        logical :: value = .false.
        class(node_type), pointer :: left => null(), right => null()
    contains
        procedure, nopass, public :: new
        procedure, public :: set_left, get_left, &
                             set_right, get_right, &
                             set_value, get_value, &
                             show
        procedure :: show_level
    end type node_type
    
contains

    function new(value) result(node)
        implicit none
        logical, intent(in) :: value
        class(node_type), pointer :: node
        integer :: status
        allocate(node, source=node_type(value, null(), null()), stat=status)
        if (status /= 0) then
            write (unit=error_unit, fmt="(A)") "# error: can not allocate node"
        end if
    end function new

    function get_value(node) result(value)
        implicit none
        class(node_type), intent(in) :: node
        logical :: value
        value = node%value
    end function get_value

    subroutine set_value(node, value)
        implicit none
        class(node_type), intent(inout) :: node
        logical, intent(in) :: value
        node%value = value
    end subroutine set_value

    function get_left(node) result(child)
        implicit none
        class(node_type), intent(in) :: node
        class(node_type), pointer :: child
        child => node%left
    end function get_left

    subroutine set_left(node, child)
        implicit none
        class(node_type), intent(inout) :: node
        class(node_type), target, intent(in) :: child
        node%left => child
    end subroutine set_left

    subroutine set_right(node, child)
        implicit none
        class(node_type), intent(inout) :: node
        class(node_type), target, intent(in) :: child
        node%right => child
    end subroutine set_right

    function get_right(node) result(child)
        implicit none
        class(node_type), intent(in) :: node
        class(node_type), pointer :: child
        child => node%right
    end function get_right

    subroutine show(node)
        implicit none
        class(node_type), intent(in) :: node
        character(len=0) :: indent = ""
        call node%show_level(indent)
    end subroutine show

    recursive subroutine show_level(node, indent)
        implicit none
        class(node_type), intent(in) :: node
        character(len=*), intent(in) :: indent
        class(node_type), pointer :: child
        write (unit=output_unit, fmt="(A, L)") indent, node%get_value()
        child => node%get_left()
        if (associated(child)) call child%show_level(indent // '  ')
        child => node%get_right()
        if (associated(child)) call child%show_level(indent // '  ')
    end subroutine show_level

end module node_mod
