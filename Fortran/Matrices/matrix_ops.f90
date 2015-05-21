module matrix_ops
    use :: precision_defs, only : dp
    implicit none
    private
    public :: init_matrix, print_matrix, print_vector

contains

    subroutine init_matrix(A)
        implicit none
        real(kind=dp), dimension(:,:), intent(out) :: A
        integer :: i, j
        do j = 1, size(A, 2)
            do i = 1, size(A, 1)
                call random_number(A(i, j))
            end do
        end do
    end subroutine init_matrix

    subroutine print_matrix(A, label)
        implicit none
        real(kind=dp), dimension(:,:), intent(in) :: A
        character(len=*), optional, intent(in) :: label
        integer :: i
        character(len=40) :: format_str
        if (present(label)) then
            write (*, "(2A)") label, ":"
        end if
        write (format_str, "(A,I3,A)") "(", size(A, 2), "(F8.3))"
        do i = 1, size(A, 1)
            write (*, format_str) A(i, :)
        end do
    end subroutine print_matrix

    subroutine print_vector(v, label)
        implicit none
        real(kind=dp), dimension(:), intent(in) :: v
        character(len=*), optional, intent(in) :: label
        character(len=40) :: format_str
        if (present(label)) then
            write (*, "(2A)") label, ":"
        end if
        write (format_str, "(A,I3,A)") "(", size(v), "(F8.3))"
        write (*, format_str) v(:)
    end subroutine print_vector

end module matrix_ops
