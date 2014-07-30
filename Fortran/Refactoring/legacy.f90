program legacy
    use, intrinsic :: iso_fortran_env
    implicit none
    integer, parameter :: sp = REAL32
    integer :: m, n, i, j
    real(kind=sp), allocatable, dimension(:, :) :: matrix
    real(kind=sp), allocatable, dimension(:) :: row
    real(kind=sp) :: alpha, x
    integer :: total_large, total_small
    character(len=40) :: buffer
    
    if (command_argument_count() == 2) then
        call get_command_argument(1, buffer)
        read (buffer, "(I6)") m
        call get_command_argument(2, buffer)
        read (buffer, "(I6)") n
    else
        m = 4
        n = 5
    end if

    allocate(matrix(m, n))
    allocate(row(n))
    do j = 1, n
        row(j) = row_func(j)
    end do
    do i = 1, m
        alpha = computationally_heavy(i)
        do j = 1, n
            matrix(i, j) = alpha + whatever(j)
        end do
    end do
    matrix(2, :) = row
    if (m <= 5 .and. n <= 5) call print_matrix(matrix)
    total_small = 0
    total_large = 0
    do i = 1, m
        do j = 1, n
            x = matrix(i, j)
            if (x < 0.1_sp) total_small = total_small + 1
            if (x > 0.9_sp) total_large = total_large + 1
        end do
    end do
    print "(A, I10)", "small: ", total_small
    print "(A, I10)", "large: ", total_large
    deallocate(matrix)
    deallocate(row)

contains

    include "functions.f90"

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
