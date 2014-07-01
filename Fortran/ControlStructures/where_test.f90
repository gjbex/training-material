program where_test
use, intrinsic :: iso_fortran_env
implicit none
integer, parameter :: N = 5, sp = REAL32
real(kind=sp), dimension(N, N) :: A
integer, dimension(N, N) :: Pos, Neg
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

where (A >= 0.0_sp)
    Pos = 1
    Neg = 0
elsewhere (A < 0.0_sp)
    Pos = 0
    Neg = 1
end where
    
do i = 1, N
    print r_fmt_str, A(i, :)
end do
print *, '---------'
do i = 1, N
    print i_fmt_str, Pos(i, :)
end do
print *, '---------'
do i = 1, N
    print i_fmt_str, Neg(i, :)
end do

if (sum(Pos + Neg) /= N*N) then
    print *, '# error: not all covered'
end if

end program where_test
