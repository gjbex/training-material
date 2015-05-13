module linked_list_mod
    use, intrinsic :: iso_fortran_env, only : dp => REAL64, &
                                              error_unit, &
                                              output_unit
    implicit none

    private
    type :: element_type
        real(kind=dp) :: value = 0.0_dp
        class(element_type), pointer :: next => null()
    contains
        procedure, nopass, public :: new_element
        procedure, public :: get_value
        procedure, public :: get_next
        procedure, public :: set_value
        procedure, public :: set_next
        procedure, public :: print_element
    end type element_type

    type, public :: list_type
        private
        class(element_type), pointer :: first => null(), last => null()
        integer :: length
    contains
        procedure, public :: prepend
        procedure, public :: shift
        procedure, public :: append
        procedure, public :: pop
        procedure, public :: is_empty
        procedure, public :: insert
!        procedure, public :: remove
        procedure, public :: get_length
        procedure, public :: get
!        procedure, public :: print_list
    end type list_type

contains

    function new_element(value) result(element)
        implicit none
        real(kind=dp), intent(in) :: value
        class(element_type), pointer :: element
        integer :: istat
        allocate(element, source=element_type(value, null()), stat=istat)
        if (istat /= 0) then
            write (unit=error_unit, fmt='(A)') &
                    '# error: can not allocate list element'
            stop
        end if
    end function new_element

    pure function get_value(self) result(value)
        implicit none
        class(element_type), intent(in) :: self
        real(kind=dp) :: value
        value = self%value
    end function get_value

    function get_next(self) result(next)
        implicit none
        class(element_type), intent(in) :: self
        class(element_type), pointer :: next
        next => self%next
    end function get_next

    subroutine set_value(self, value)
        implicit none
        class(element_type), intent(inout) :: self
        real(kind=dp), intent(in) :: value
        self%value = value
    end subroutine set_value

    subroutine set_next(self, next)
        implicit none
        class(element_type), intent(inout) :: self
        class(element_type), pointer, intent(in) :: next
        self%next => next
    end subroutine set_next

    subroutine print_element(self)
        implicit none
        class(element_type), intent(in) :: self
        write (unit=output_unit, fmt='(F10.4)') self%value
    end subroutine print_element

    function new_list() result(list)
        implicit none
        class(list_type), pointer :: list
        integer :: istat
        allocate(list, source=list_type(null(), null(), 0), stat=istat)
        if (istat /= 0) then
            write (unit=error_unit, fmt='(A)') &
                    '# error: can not allocate list'
            stop
        end if
    end function new_list

    subroutine prepend(self, value)
        implicit none
        class(list_type), intent(inout) :: self
        real(kind=dp), intent(in) :: value
        class(element_type), pointer :: element
        element => new_element(value)
        if (.not. associated(self%first)) then
            self%first => element
            self%last => element
        else
            element%next => self%first
            self%first => element
        end if
        self%length = self%length + 1
    end subroutine prepend

    subroutine append(self, value)
        implicit none
        class(list_type), intent(inout) :: self
        real(kind=dp), intent(in) :: value
        class(element_type), pointer :: element
        element => new_element(value)
        if (.not. associated(self%first)) then
            self%first => element
            self%last => element
        else
            self%last%next => element
            self%last => element
        end if
        self%length = self%length + 1
    end subroutine append

    function shift(self) result(value)
        implicit none
        class(list_type), intent(inout) :: self
        real(kind=dp) :: value
        class(element_type), pointer :: tmp
        if (self%is_empty()) then
            write (unit=error_unit, fmt='(A)') &
                '# error: can not shift from empty list'
            stop
        end if
        value = self%first%value
        if (self%get_length() == 1) then
            deallocate(self%first)
            self%first => null()
            self%last => null()
        else
            tmp => self%first
            self%first => tmp%next
            deallocate(tmp)
        end if
        self%length = self%length - 1
    end function shift

    function pop(self) result(value)
        implicit none
        class(list_type), intent(inout) :: self
        real(kind=dp) :: value
        class(element_type), pointer :: tmp
        if (self%is_empty()) then
            write (unit=error_unit, fmt='(A)') &
                '# error: can not shift from empty list'
            stop
        end if
        value = self%last%value
        if (self%get_length() == 1) then
            deallocate(self%last)
            self%first => null()
            self%last => null()
        else
            tmp => self%first
            do while (.not. associated(tmp%next, self%last))
                tmp => tmp%next
            end do 
            self%last => tmp
            deallocate(tmp%next)
            tmp%next => null()
        end if
        self%length = self%length - 1
    end function pop

    subroutine insert(self, pos, value)
        implicit none
        class(list_type), intent(inout) :: self
        integer, intent(in) :: pos
        real(kind=dp), intent(in) :: value
        class(element_type), pointer :: tmp, pos_tmp
        integer :: i
        if (pos < 0 .or. pos > self%get_length() + 1) then
            write (unit=error_unit, fmt='(A)') &
                '# error insert position out of bounds'
            stop
        end if
        if (pos == 1) then
            call self%prepend(value)
        else if (pos == self%get_length() + 1) then
            call self%append(value)
        else
            pos_tmp => self%first
            do i = 2, pos - 1
                pos_tmp => pos_tmp%next
            end do
            tmp => new_element(value)
            tmp%next => pos_tmp%next
            pos_tmp%next => tmp
            self%length = self%length + 1
        end if
    end subroutine insert

    function get(self, pos) result(value)
        implicit none
        class(list_type), intent(in) :: self
        integer, intent(in) :: pos
        real(kind=dp) :: value
        class(element_type), pointer :: tmp
        integer :: i
        if (pos < 0 .or. pos > self%get_length()) then
            write (unit=error_unit, fmt='(A)') &
                '# error get position out of bounds'
            stop
        end if
        tmp => self%first
        do i = 2, pos
            tmp => tmp%next
        end do
        value = tmp%value
    end function get

    pure integer function get_length(self)
        implicit none
        class(list_type), intent(in) :: self
        get_length = self%length
    end function get_length

    pure logical function is_empty(self)
        implicit none
        class(list_type), intent(in) :: self
        is_empty = self%get_length() == 0
    end function is_empty

end module linked_list_mod
