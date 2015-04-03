program pointer_test
    use, intrinsic :: iso_fortran_env
    use matrix_ops
    implicit none
    integer, parameter :: m = 5, n = 4
    real(kind=REAL64), dimension(:, :), allocatable, target :: a
    real(kind=REAL64), dimension(:, :), pointer :: p => null()

    allocate(A(m, n))
    if (.not. associated(p)) &
        print '(A)', '# p not associated'
    p => A
    if (associated(p)) &
        print '(A)', '# p associated'
    call init_matrix(p)
    call print_matrix(p, 'A')
    deallocate(A)
    if (associated(p)) &
        print '(A)', '# p still associated'
    p => null()
    if (.not. associated(p)) &
        print '(A)', '# p not associated'

end program pointer_test
