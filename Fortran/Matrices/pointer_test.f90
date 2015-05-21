program pointer_test
    use, intrinsic :: iso_fortran_env, only :REAL32, REAL64
    use :: matrix_ops, only : init_matrix, print_matrix
    implicit none
    integer, parameter :: m = 5, n = 4
    real(kind=REAL64), dimension(:, :), allocatable, target :: a
    real(kind=REAL64), dimension(:, :), pointer :: p => null()

    if (.not. associated(p)) &
        print '(A)', '#1 p not associated'
    p => A
    print '(A)', '#2 p => A'
    if (.not. associated(p)) &
        print '(A)', '#3 p still not associated'
    allocate(A(m, n))
    print '(A)', '#4 allocate A'
    if (.not. associated(p)) &
        print '(A)', '#5 A allocated, but p not associated'
    p => A
    print '(A)', '#6 p => A'
    if (associated(p) .and. associated(p, A)) &
        print '(A)', '#7 p associated to A'
    call init_matrix(p)
    print '(A)', '#8 initialize and print p'
    call print_matrix(p, 'A')
    deallocate(A)
    print '(A)', '#9 A deallocated'
    if (associated(p)) &
        print '(A)', '#10 p still associated'
    if (.not. associated(p, A)) &
        print '(A)', '#11 p associated, but not to A'
    p => null()
    print '(A)', '#12 p => null()'
    if (.not. associated(p)) &
        print '(A)', '#13 p not associated'
    print '(A)', '#14 done'

end program pointer_test
