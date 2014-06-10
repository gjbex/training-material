module matrix_ops
    implicit none
    public :: init_matrix, print_matrix

contains

    subroutine init_matrix(A)
        implicit none
        double precision, dimension(:,:), intent(out) :: A
        integer :: i, j
        integer, dimension(2) :: dims
        dims = shape(A)
        do i = 1, dims(1)
            do j = 1, dims(2)
                call random_number(A(i, j))
            end do
        end do
    end subroutine init_matrix

    subroutine print_matrix(A, label)
        implicit none
        double precision, dimension(:,:), intent(in) :: A
        character(len=:), allocatable, optional, intent(in) :: label
        integer :: i, j
        integer, dimension(2) :: dims
        character(len=40) :: format_str
        if (present(label)) then
            write (*, "(2A)") label, ":"
        end if
        dims = shape(A)
        write (format_str, "(A,I3,A)") "(", dims(2), "(F6.3))"
        do i = 1, dims(1)
            write (*, format_str) A(i, :)
        end do
    end subroutine print_matrix

end module matrix_ops

