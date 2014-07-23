module id_node_mod
    use, intrinsic :: iso_fortran_env
    use node_mod
    implicit none

    private
    integer :: global_id = 1
    type, extends(node_type), public :: id_node_type
        private
        integer :: id = 1
    contains
        procedure, nopass, public :: new
        procedure, public :: get_id
        procedure :: show_level
    end type id_node_type

contains

    function new() result(node)
        implicit none
        class(node_type), pointer :: node
        integer :: status
        global_id = global_id + 1
        allocate(node, source=id_node_type(id=global_id), &
                 stat=status)
        if (status /= 0) then
            write (unit=error_unit, fmt="(A)") &
                    "# error: can not allocate node"
            stop
        end if
    end function new

    function get_id(node) result(id)
        implicit none
        class(id_node_type), intent(in) :: node
        integer :: id
        id = node%id
    end function get_id

    recursive subroutine show_level(node, indent)
        implicit none
        class(id_node_type), intent(in) :: node
        character(len=*), intent(in) :: indent
        class(node_type), pointer :: child
        write (unit=output_unit, fmt="(A, I3, A, F6.3)") &
                indent, node%get_id(), ": ", node%get_value()
        child => node%get_left()
        if (associated(child)) &
            call child%show_level(indent // '  ')
        child => node%get_right()
        if (associated(child)) &
            call child%show_level(indent // '  ')
    end subroutine show_level

end module id_node_mod
