program where_test
    use, intrinsic :: iso_fortran_env, only : sp => REAL32, error_unit
    implicit none
    integer, parameter :: N = 5
    real, parameter :: eps = 1.0e-2_sp
    real(kind=sp), dimension(N, N) :: A
    integer, dimension(N, N) :: Pos, Neg, Zero
    real(kind=sp) :: r
    integer :: i, j
    character(len=40) :: r_fmt_str
    character(len=40) :: i_fmt_str

    write (r_fmt_str, "('(', I2, 'F7.2)')") N
    write (i_fmt_str, "('(', I2, 'I7)')") N

    do i = 1, N
        do j = 1, N
            call random_number(r)
            A(i, j) = 2.0_sp*(r - 0.5_sp)
        end do
    end do

    where (A > eps)
        Pos = 1
        Neg = 0
        Zero = 0
    elsewhere (A < eps)
        Pos = 0
        Neg = 1
        Zero = 0
    elsewhere
        Pos = 0
        Neg = 0
        Zero = 1
    end where

    print '(A)', 'matrix:'
    do i = 1, N
        print r_fmt_str, A(i, :)
    end do
    print '(2A)', '---------', 'positive'
    do i = 1, N
        print i_fmt_str, Pos(i, :)
    end do
    print '(2A)', '---------', 'negative'
    do i = 1, N
        print i_fmt_str, Neg(i, :)
    end do
    print '(2A)', '---------', 'zero'
    do i = 1, N
        print i_fmt_str, Zero(i, :)
    end do

    if (sum(Pos + Neg + Zero) /= N*N) then
        write (unit=error_unit, fmt='(A)') '# error: not all covered'
        stop 1
    end if

end program where_test
