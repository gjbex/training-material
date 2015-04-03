program pointer_test
    use, intrinsic :: iso_fortran_env
    use matrix_ops
    implicit none
    integer, parameter :: m = 5, n = 4
    real(kind=REAL64), dimension(:, :), allocatable, target :: a
    real(kind=REAL64), dimension(:, :), pointer :: p => null()

    allocate(A(m, n))
    p => A
    call init_matrix(p)
    call print_matrix(p, 'A')
    deallocate(A)

end program pointer_test
