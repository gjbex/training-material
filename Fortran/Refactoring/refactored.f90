program refactored
    use data_mod
    implicit none
    integer, parameter :: m = 4, n = 5
    integer :: i, j
    type(data_type) :: matrix
    real(kind=sp) :: alpha, total
    
    call matrix%allocate_data(m, n)
    do i = 1, m
        alpha = computationally_heavy(i)
        do j = 1, n
            call matrix%set(i, j, alpha + whatever(j))
        end do
    end do
    total = 0.0_sp
    do i = 1, m
        alpha = computationally_heavy(i)
        do j = 1, n
            total = total + matrix%get(i, j)/alpha - whatever(j)
        end do
    end do
    print "(E12.5)", total
    call matrix%deallocate_data()

contains

    real(kind=sp) function computationally_heavy(n)
        implicit none
        integer, intent(in) :: n
        computationally_heavy = 0.3_sp**n
    end function computationally_heavy

    real(kind=sp) function whatever(n)
        implicit none
        integer, intent(in) :: n
        whatever = 1.2_sp**n
    end function whatever

end program refactored
