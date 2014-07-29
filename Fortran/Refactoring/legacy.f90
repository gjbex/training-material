program legacy
    use, intrinsic :: iso_fortran_env
    implicit none
    integer, parameter :: sp = REAL32
    integer, parameter :: m = 4, n = 5
    integer :: i, j
    real(kind=sp), allocatable, dimension(:, :) :: matrix
    real(kind=sp) :: alpha, total
    
    allocate(matrix(m, n))
    do i = 1, m
        alpha = computationally_heavy(i)
        do j = 1, n
            matrix(i, j) = alpha + whatever(j)
        end do
    end do
    total = 0.0_sp
    do i = 1, m
        alpha = computationally_heavy(i)
        do j = 1, n
            total = total + matrix(i, j)/alpha - whatever(j)
        end do
    end do
    print "(E12.5)", total
    deallocate(matrix)

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

end program legacy
