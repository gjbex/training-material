!> @brief module implementing a binary tree
!>
!> This module implements a user defined bype to represent nodes in
!> a binary tree.  It also implements a few methods that work on trees.
module node_mod
    use, intrinsic :: iso_fortran_env
    implicit none

    private
    !> @private
    !> @brief kind for the floating point value that is stored by
    !>        the node
    integer, parameter :: sp = REAL32
    !> @brief User defined type representing a node
    type, public :: node_type
        private
        !> @private
        !> value stored in the node, single precision floating point
        real(kind=sp) :: value = 0.0_sp
        !> @private
        !> left child of the node, pointer to `node_type`
        class(node_type), pointer :: left => null()
        !> @private
        !> right child of the node, pointer to `node_type`
        class(node_type), pointer :: right => null()
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

    !> @brief constructor for a new node
    !> 
    !> This constructor will initialize the node's value to zero,
    !> and its left and right child to `null()`, i.e., the node has
    !> no children.
    !>
    !> @returns new `node_type` object
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

    !> @brief get the node's value
    !> @param[in] node node to retrieve the value from, single
    !> @returns node's value, precision floating point
    function get_value(node) result(value)
        implicit none
        class(node_type), intent(in) :: node
        real(kind=sp) :: value
        value = node%value
    end function get_value

    !> @brief set the node's value
    !> @param[inout] node  node to set the value of
    !> @param[in]    value new value for the node, single precision
    !>                     floating point
    subroutine set_value(node, value)
        implicit none
        class(node_type), intent(inout) :: node
        real(kind=sp), intent(in) :: value
        node%value = value
    end subroutine set_value

    !> @brief get a pointer to the left child
    !> @param[in] node node to retrieve the left child from
    !> @returns pointer to the left child, `null()` if the node has
    !>          no left child
    function get_left(node) result(child)
        implicit none
        class(node_type), intent(in) :: node
        class(node_type), pointer :: child
        child => node%left
    end function get_left

    !> @brief set the node's left child
    !> @param[inout] node  node to set the left child for
    !> @param[in]    child node that is to be the left child
    subroutine set_left(node, child)
        implicit none
        class(node_type), intent(inout) :: node
        class(node_type), target, intent(in) :: child
        node%left => child
    end subroutine set_left

    !> @brief set the node's right child
    !> @param[inout] node  node to set the right child for
    !> @param[in]    child node that is to be the right child
     subroutine set_right(node, child)
        implicit none
        class(node_type), intent(inout) :: node
        class(node_type), target, intent(in) :: child
        node%right => child
    end subroutine set_right

    !> @brief get a pointer to the right child
    !> @param[in] node node to retrieve the right child from
    !> @returns pointer to the right child, `null()` if the node has
    !>          no right child
    function get_right(node) result(child)
        implicit none
        class(node_type), intent(in) :: node
        class(node_type), pointer :: child
        child => node%right
    end function get_right

    !> @brief print a string representation of the node, and all
    !>        its children
    !>
    !> This method is typically applied to the root of the tree.
    !>
    !> @param[in] node node to print the string representation for
    subroutine show(node)
        implicit none
        class(node_type), intent(in) :: node
        character(len=0) :: indent
        indent = ""
        call node%show_level(indent)
    end subroutine show

    !> @private
    !> @brief recursive function to print the node and its children
    !>
    !> Recursively descend down the tree, incrementing the indentation
    !. for each subsequent level.
    !>
    !> @param[in] node   node to print
    !> @param[in] indent current indentation string
    recursive subroutine show_level(node, indent)
        implicit none
        class(node_type), intent(in) :: node
        character(len=*), intent(in) :: indent
        class(node_type), pointer :: child
        write (unit=output_unit, fmt="(A, F6.3)") indent, &
            node%get_value()
        child => node%get_left()
        if (associated(child)) &
            call child%show_level(indent // '  ')
        child => node%get_right()
        if (associated(child)) &
            call child%show_level(indent // '  ')
    end subroutine show_level

    !> @brief initialize a random tree starting from the root node
    !>
    !> The tree is built randomly starting from the root.  Whether
    !> a node has children depends on a probability that will decrease
    !> with the depth of the tree.
    !>
    !> The value of the nodes can either be the same for all nodes,
    !> or, if not specified, it will be drawn from a uniform random
    !> distribution between 0 and 1.
    !>
    !> @param[inout] node   node representing the root of the tree
    !> @param[in]    prob   probability that the node will have a left
    !>                      and/or a right child
    !> @param[in]    factor factor used as a multiplicator at each
    !>                      level of the tree to reduce the probability
    !>                      that a node has children, expected to
    !>                      be between 0 and 1
    !> @param[in]    value  optional argument specifying the value for
    !>                      the nodes, if not present, nodes are
    !>                      assigned random values
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
            if (present(value)) then
                call child%init_random(prob*factor, factor, value)
            else
                call child%init_random(prob*factor, factor)
            end if
        end if
        call random_number(r)
        if (r < prob) then
            child => node%new()
            call node%set_right(child)
            if (present(value)) then
                call child%init_random(prob*factor, factor, value)
            else
                call child%init_random(prob*factor, factor)
            end if
        end if
    end subroutine init_random

    !> @brief count the number of nodes in the tree
    !> @param[in] node node representing the root of the tree
    !> @returns the number of nodesin the tree
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

    !> @brief compute the maximum distance to a leaf, starting from
    !>        the given node
    !>
    !> The distance from one node to another is computed as the sum
    !> of the values of all the nodes on the path from the first to
    !> the second, inclusive. The leaf distance from a given node is
    !> defined as the distance between this node, and on of its
    !> descendants such that this is the maximum distance from all
    !> descendants of that node.
    !>
    !> @param[in] node node node to start computing distances from
    !> @returns largest distance to a leaf from the given node
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

    !> @brief ensures that all memory allocated to nodes in the tree
    !>        is properly deallocated
    !> @param[inout] node node representing the root of the tree
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
