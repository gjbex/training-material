module matrix_mod
    implicit none
    public :: print_matrix

contains

    subroutine print_matrix(a)
        real(kind=8), dimension(:,:), intent(in) :: a
        integer :: c, r
        do r = 1, size(a, 1)
            print *, a(r,:)
        end do
end subroutine print_matrix

end module matrix_mod
