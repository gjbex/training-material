program alloc_test
    use :: precision_defs, only : dp
    use :: matrix_ops, only : init_matrix, print_matrix
    implicit none
    integer :: M, N, i, j
    real(kind=dp), allocatable, dimension(:,:) :: A
    character(len=1024) :: buffer
    character(len=:), allocatable :: label_str

    select case (command_argument_count())
        case (2)
            call get_command_argument(1, buffer)
            read (buffer, "(I20)") M
            call get_command_argument(2, buffer)
            read (buffer, "(I20)") N
        case (1)
            call get_command_argument(1, buffer)
            read (buffer, "(I20)") M
            N = M
        case default
            M = 4
            N = 5
    end select

    if (.not. allocated(A)) print '(A)', '# A not allocated yet'
    allocate(A(M, N))
    if (allocated(A)) print '(A)', '# A allocated'
    call init_matrix(A)
    label_str = "A"
    call print_matrix(A, label=label_str)
    A = reshape([ ((i*size(A, 2) + j, i = 0, size(A, 1) - 1), &
                   j = 1, size(A, 2)) ], shape(A))
    call print_matrix(A, "A'")
    deallocate(A)
    if (.not. allocated(A)) print '(A)', '# A no longer allocated'

end program alloc_test
