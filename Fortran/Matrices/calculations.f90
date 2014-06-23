program calculations
    use, intrinsic :: iso_fortran_env
    use matrix_ops
    implicit none
    integer, parameter :: M = 5, N = 5
    real(kind=REAL64), dimension(M, N) :: A, B, C
    character(len=:), allocatable :: label_str

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

end program calculations

