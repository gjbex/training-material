program forall_test
    use, intrinsic :: iso_fortran_env, only : sp => REAL32
    implicit none
    integer, parameter :: N = 5
    real(kind=sp), dimension(N, N) :: A
    integer :: i, j
    character(len=40) :: fmt_str

    write (fmt_str, "('(', I2, 'F5.2)')") N

    A = 0.0_sp
    forall (i = 1:N, j = 1:N, i == j - 1 .or. i == j + 1)
        A(i, j) = 1.0_sp
    end forall

    do i = 1, N
        print fmt_str, A(i, :)
    end do

end program forall_test
