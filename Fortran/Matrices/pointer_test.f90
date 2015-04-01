program pointer_test
    use iso_fortran_env
    use matrix_ops
    implicit none
    integer, parameter :: m = 5, n = 4
    real(kind=REAL64), dimension(:, :), allocatable, target :: a
    real(kind=REAL64), dimension(:, :), pointer :: p
    character(len=:), allocatable :: label

    allocate(A(m, n))
    p => A
    call init_matrix(p)
    label = 'A'
    call print_matrix(p, label)
    deallocate(A)

end program pointer_test
