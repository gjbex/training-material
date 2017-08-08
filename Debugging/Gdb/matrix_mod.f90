module matrix_mod
    use, intrinsic :: iso_fortran_env, only : dp => REAL64
    implicit none
    public :: print_matrix

contains

    subroutine print_matrix(a)
        real(kind=dp), dimension(:,:), intent(in) :: a
        integer :: r
        do r = 1, size(a, 1)
            print *, a(r, :)
        end do
    end subroutine print_matrix

end module matrix_mod
