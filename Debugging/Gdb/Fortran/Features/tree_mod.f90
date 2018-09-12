module tree_mod
    use, intrinsic :: iso_fortran_env, only : error_unit
    implicit none

    type, private :: node_ptr_type
        private
        class(node_type), pointer :: obj
    end type node_ptr_type

    type, public :: node_type
        private
        class(node_ptr_type), dimension(:), allocatable :: children
        real :: value
    contains
        procedure, nopass, public :: new
        procedure, public :: get_value
        procedure, public :: set_value
        procedure, public :: get_nr_children
        procedure, public :: set_child
        procedure, public :: get_child
        procedure, public :: show
        procedure, public :: visit
    end type node_type

    integer, protected :: allocation_err = 10, &
                          invalid_child_index_err = 11
                        
contains

    function new(value, nr_children) result(node)
        implicit none
        real, intent(in) :: value
        integer, intent(in) :: nr_children
        class(node_type), pointer :: node
        integer :: child_nr, ierr
        allocate(node, stat=ierr)
        if (ierr /= 0) then
            write (unit=error_unit, fmt='(A)') &
                '### error: can not allocate node'
            stop allocation_err
        end if
        node%value = value
        allocate(node%children(nr_children), stat=ierr)
        if (ierr /= 0) then
            write (unit=error_unit, fmt='(A)') &
                '### error: can not allocate node children'
            stop allocation_err
        end if
        do child_nr = 1, nr_children
            node%children(child_nr)%obj => null()
        end do
    end function new

    real function get_value(this)
        implicit none
        class(node_type), intent(in) :: this
        get_value = this%value
    end function get_value

    subroutine set_value(this, value)
        implicit none
        class(node_type), intent(inout) :: this
        real, intent(in) :: value
        this%value = value
    end subroutine set_value

    integer function get_nr_children(this)
        implicit none
        class(node_type), intent(in) :: this
        get_nr_children = size(this%children)
    end function get_nr_children

    subroutine set_child(this, child_nr, child)
        implicit none
        class(node_type), intent(inout) :: this
        integer, intent(in) :: child_nr
        class(node_type), pointer, intent(in) :: child
        if (child_nr > this%get_nr_children() .or. child_nr < 1) then
            write(unit=error_unit, fmt='(A, I3, A, I3, A)') &
                '### error: invalid child index ', child_nr, &
                ', node has ', this%get_nr_children(), ' children'
            stop invalid_child_index_err
        end if
        this%children(child_nr)%obj => child
    end subroutine set_child

    function get_child(this, child_nr) result(child)
        implicit none
        class(node_type), intent(in) :: this
        integer, intent(in) :: child_nr
        class(node_type), pointer :: child
        if (child_nr > this%get_nr_children() .or. child_nr < 1) then
            write(unit=error_unit, fmt='(A, I3, A, I3, A)') &
                '### error: invalid child index ', child_nr, &
                ', node has ', this%get_nr_children(), ' children'
            stop invalid_child_index_err
        end if
        child => this%children(child_nr)%obj
    end function get_child

    recursive subroutine show(this, indent)
        implicit none
        class(node_type), intent(in) :: this
        integer, intent(in), optional :: indent
        integer :: child_nr, indentation
        class(node_type), pointer :: child
        character(len=32) :: fmt_str
        if (present(indent)) then
            indentation = indent
        else
            indentation = 2
        end if
        write (fmt_str, '(A, I0, A)') &
            '(A', indentation, ', ES15.3, A, I3)'
        print fmt_str, '', this%get_value(), &
            ', children: ', this%get_nr_children()
        do child_nr = 1, this%get_nr_children()
            child => this%get_child(child_nr)
            call child%show(indentation + 2)
        end do
    end subroutine show

    recursive subroutine visit(this, transformation)
        implicit none
        class(node_type), intent(inout) :: this
        interface
            real function transformation(value)
                implicit none
                real, intent(in) :: value
            end function transformation
        end interface
        integer :: child_nr
        class(node_type), pointer :: child
        call this%set_value(transformation(this%get_value()))
        do child_nr = 1, this%get_nr_children()
            child => this%get_child(child_nr)
            call child%visit(transformation)
        end do
    end subroutine visit

    recursive subroutine finalize(this)
        implicit none
        type(node_type), pointer, intent(inout) :: this
        type(node_type), pointer :: child
        integer :: child_nr
        do child_nr = 1, this%get_nr_children()
            child => this%get_child(child_nr)
            if (associated(child)) then
                call finalize(child)
            end if
        end do
        deallocate(this)
    end subroutine finalize

end module tree_mod
