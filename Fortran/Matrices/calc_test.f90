program calc_test
    use, intrinsic :: iso_fortran_env, only : dp => REAL64
    use matrix_ops, only : init_matrix, print_matrix, print_vector
    implicit none
    integer, parameter :: M = 5, N = 5, P = 3
    real(kind=dp), dimension(M, N) :: A, B, C
    real(kind=dp), dimension(M, P) :: D
    real(kind=dp), dimension(M) :: col_max
    real(kind=dp), dimension(P) :: row_sum
    character(len=:), allocatable :: label_str
    integer :: nr_large

    ! initialize matrix A
    call init_matrix(A)
    label_str = "A"
    call print_matrix(A, label=label_str)

    ! initialize matrix B
    call init_matrix(B)
    label_str = "B"
    call print_matrix(B, label=label_str)

    ! matrix sum
    C = A + B
    label_str = "A + B"
    call print_matrix(C, label=label_str)

    ! element-wise product
    C = A * B
    label_str = "A * B"
    call print_matrix(C, label=label_str)

    ! element-wise division
    C = A/B
    label_str = "A/B"
    call print_matrix(C, label=label_str)

    ! element-wise power
    C = A**2
    label_str = "A**2"
    call print_matrix(C, label=label_str)

    ! matrix product
    C = matmul(A, B)
    label_str = "A . B"
    call print_matrix(C, label=label_str)

    ! element-wise addition of constant
    C = 2.0_dp + A
    label_str = "2 + A"
    call print_matrix(C, label=label_str)

    ! element-wise multiplication of constant
    C = 3.0_dp*A
    label_str = "3*A"
    call print_matrix(C, label=label_str)

    ! initialize matrix D
    call init_matrix(D)
    label_str = "D"
    call print_matrix(D, label=label_str)

    ! row sum
    row_sum = sum(D, dim=1)
    label_str = 'row sum D'
    call print_vector(row_sum, label=label_str)

    ! column maximum
    col_max = maxval(D, dim=2)
    label_str = 'column max D'
    call print_vector(col_max, label=label_str)

    ! number of elements larger than 0.5
    nr_large = count(D > 0.5)
    label_str = 'number elements D > 0.5'
    print '(A, ": ", I0)', label_str, nr_large

    ! check whether any element < 0.01
    if (any(D < 0.01)) then
        print *, 'Some elements < 0.01'
    else
        print *, 'no elements < 0.01'
    end if

end program calc_test

