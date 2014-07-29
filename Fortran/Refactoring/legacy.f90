program legacy
    use, intrinsic :: iso_fortran_env
    implicit none
    integer, parameter :: sp = REAL32
    integer, parameter :: m = 4, n = 5
    integer :: i, j
    real(kind=sp), allocatable, dimension(:, :) :: matrix
    real(kind=sp), allocatable, dimension(:) :: row
    real(kind=sp) :: alpha, total
    
    allocate(matrix(m, n))
    allocate(row(n))
    do j = 1, n
        row(j) = 2.0_sp*j
    end do
    do i = 1, m
        alpha = computationally_heavy(i)
        do j = 1, n
            matrix(i, j) = alpha + whatever(j)
        end do
    end do
    matrix(2, :) = row
    call print_matrix(matrix)
    total = 0.0_sp
    do i = 1, m
        alpha = computationally_heavy(i)
        do j = 1, n
            total = total + matrix(i, j)/alpha - whatever(j)
        end do
    end do
    print "(E12.5)", total
    deallocate(matrix)
    deallocate(row)

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

    subroutine print_matrix(m)
        implicit none
        real(kind=sp), dimension(:, :), intent(in) :: m
        integer, dimension(2) :: dims
        integer :: i
        character(len=20) :: fmt_str
        dims = shape(m)
        write (fmt_str, "('(', I2, 'E13.5)')") dims(2)
        write (unit=output_unit, fmt="(A)") "matrix"
        do i = 1, dims(1)
            write (unit=output_unit, fmt=fmt_str) m(i, :)
        end do
    end subroutine print_matrix

end program legacy
