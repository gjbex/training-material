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
    end type element_type

    type, public :: list_type
        private
        class(element_type), pointer :: first => null(), last => null()
        integer :: length
    contains
        procedure, public :: unshift
        procedure, public :: shift
        procedure, public :: push
        procedure, public :: pop
        procedure, public :: is_empty
        procedure, public :: insert
        procedure, public :: remove
        procedure, public :: get_length
        procedure, public :: get
        procedure, public :: clear
        procedure, public :: print_list
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

    subroutine unshift(self, value)
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
    end subroutine unshift

    subroutine push(self, value)
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
    end subroutine push

    subroutine shift(self, value)
        implicit none
        class(list_type), intent(inout) :: self
        real(kind=dp), intent(out), optional :: value
        class(element_type), pointer :: tmp
        if (self%is_empty()) then
            write (unit=error_unit, fmt='(A)') &
                '# error: can not shift from empty list'
            stop
        end if
        if (present(value)) value = self%first%value
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
    end subroutine shift

    subroutine pop(self, value)
        implicit none
        class(list_type), intent(inout) :: self
        real(kind=dp), intent(out), optional :: value
        class(element_type), pointer :: tmp
        if (self%is_empty()) then
            write (unit=error_unit, fmt='(A)') &
                '# error: can not shift from empty list'
            stop
        end if
        if (present(value)) value = self%last%value
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
    end subroutine pop

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
            call self%unshift(value)
        else if (pos == self%get_length() + 1) then
            call self%push(value)
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

    subroutine remove(self, pos, value)
        implicit none
        class(list_type), intent(inout) :: self
        integer, intent(in) :: pos
        real(kind=dp), intent(out), optional :: value
        class(element_type), pointer :: tmp, pos_tmp
        integer :: i
        if (pos < 1 .or. pos > self%get_length()) then
            write (unit=error_unit, fmt='(A)') &
                '# error remove position out of bounds'
            stop
        end if
        if (pos == 1) then
            call self%shift(value=value)
        else if (pos == self%get_length()) then
            call self%pop(value=value)
        else
            pos_tmp => self%first
            do i = 2, pos - 1
                pos_tmp => pos_tmp%next
            end do
            tmp => pos_tmp%next
            pos_tmp%next => tmp%next
            if (present(value)) value = tmp%value
            deallocate(tmp)
            self%length = self%length - 1
        end if
    end subroutine remove

    subroutine get(self, pos, value)
        implicit none
        class(list_type), intent(in) :: self
        integer, intent(in) :: pos
        real(kind=dp), intent(out) :: value
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
    end subroutine get

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

    subroutine clear(self)
        implicit none
        class(list_type), intent(inout) :: self
        real(kind=dp) :: value
        do while (.not. self%is_empty())
            call self%shift(value=value)
        end do
    end subroutine clear

    subroutine print_list(self)
        implicit none
        class(list_type), intent(in) :: self
        integer :: i
        real(kind=dp) :: value
        do i = 1, self%get_length()
            call self%get(i, value)
            write (unit=output_unit, fmt='(F30.4)') value
        end do
    end subroutine print_list

end module linked_list_mod
