module node_mod
    use, intrinsic :: iso_fortran_env
    implicit none

    private

    type, public :: node_type
        logical :: value
        class(node_type), pointer :: left => null(), right => null()
    contains
        procedure, public :: add_left, add_right, set, show
    end type node_type
    
contains

    subroutine set(node, value)
        implicit none
        class(node_type), intent(inout) :: node
        logical, intent(in) :: value
        node%value = value
    end subroutine set

    subroutine add_left(node, child)
        implicit none
        class(node_type), intent(inout) :: node
        class(node_type), target, intent(in) :: child
        node%left => child
    end subroutine add_left

    subroutine add_right(node, child)
        implicit none
        class(node_type), intent(inout) :: node
        class(node_type), target, intent(in) :: child
        node%right => child
    end subroutine add_right

    recursive subroutine show(node)
        implicit none
        class(node_type), intent(in) :: node
        print *, node%value
        if (associated(node%left)) call node%left%show()
        if (associated(node%right)) call node%right%show()
    end subroutine show

end module node_mod
