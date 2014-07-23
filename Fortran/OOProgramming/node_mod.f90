module node_mod
    use, intrinsic :: iso_fortran_env
    implicit none

    private
    integer, parameter :: sp = REAL32
    type, public :: node_type
        private
        real(kind=sp) :: value = 0.0_sp
        class(node_type), pointer :: left => null(), right => null()
    contains
        procedure, nopass, public :: new
        procedure, public :: set_left
        procedure, public :: get_left
        procedure, public :: set_right
        procedure, public :: get_right
        procedure, public :: set_value
        procedure, public :: get_value
        procedure, public :: show
        procedure, public :: init_random
        procedure, public :: count_nodes
        procedure, public :: leaf_distance
        procedure, public :: finalize
        procedure :: show_level
    end type node_type
    
contains

    function new() result(node)
        implicit none
        class(node_type), pointer :: node
        integer :: status
        allocate(node, source=node_type(0.0_sp, null(), null()), &
                 stat=status)
        if (status /= 0) then
            write (unit=error_unit, fmt="(A)") &
                    "# error: can not allocate node"
            stop
        end if
    end function new

    function get_value(node) result(value)
        implicit none
        class(node_type), intent(in) :: node
        real(kind=sp) :: value
        value = node%value
    end function get_value

    subroutine set_value(node, value)
        implicit none
        class(node_type), intent(inout) :: node
        real(kind=sp), intent(in) :: value
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
        write (unit=output_unit, fmt="(A, F6.3)") indent, node%get_value()
        child => node%get_left()
        if (associated(child)) &
            call child%show_level(indent // '  ')
        child => node%get_right()
        if (associated(child)) &
            call child%show_level(indent // '  ')
    end subroutine show_level

    recursive subroutine init_random(node, prob, factor, value)
        implicit none
        class(node_type), intent(inout) :: node
        real(kind=sp), intent(in) :: prob, factor
        real(kind=sp), optional, intent(in) :: value
        class(node_type), pointer :: child
        real(kind=sp) :: r
        if (present(value)) then
            r = value
        else
            call random_number(r)
        end if
        call node%set_value(r)
        call random_number(r)
        if (r < prob) then
            child => node%new()
            call node%set_left(child)
            call child%init_random(prob*factor, factor)
        end if
        call random_number(r)
        if (r < prob) then
            child => node%new()
            call node%set_right(child)
            call child%init_random(prob*factor, factor)
        end if
    end subroutine init_random

    recursive function count_nodes(node) result(count)
        implicit none
        class(node_type), intent(in) :: node
        integer :: count
        class(node_type), pointer :: child
        count = 1
        child => node%get_left()
        if (associated(child)) &
            count = count + child%count_nodes()
        child => node%get_right()
        if (associated(child)) &
            count = count + child%count_nodes()
    end function count_nodes

    recursive function leaf_distance(node) result(dist)
        implicit none
        class(node_type), intent(in) :: node
        real(kind=sp) :: dist
        class(node_type), pointer :: child
        real(kind=sp) :: path1, path2
        path1 = node%get_value()
        path2 = node%get_value()
        child => node%get_left()
        if (associated(child)) &
            path1 = path1 + child%leaf_distance()
        child => node%get_right()
        if (associated(child)) &
            path2 = path2 + child%leaf_distance()
        dist = max(path1, path2)
    end function leaf_distance

    recursive subroutine finalize(node)
        implicit none
        class(node_type), intent(inout) :: node
        class(node_type), pointer :: child
        child => node%get_left()
        if (associated(child)) then
            call child%finalize()
            deallocate(child)
        end if
        child => node%get_right()
        if (associated(child)) then
            call child%finalize()
            deallocate(child)
        end if
    end subroutine finalize

end module node_mod
