program conversions
    use, intrinsic :: iso_fortran_env, only : &
        r8 => REAL64, r4 => REAL32, i8 => INT64, i4 => INT32
    implicit none
    real(kind=r8) :: x, y
    real(kind=r4) :: z
    integer(kind=i8) :: a, b
    integer(kind=i4) :: c, d
    x = 1.394e76_r8
    y = 2.37e56_r8
    z = x + y
    print '(E15.5)', z
    a = 309403103049_i8
    b = 49031944903_i8
    c = a + b
    print '(I15)', c
    d = z
    print '(I15)', d
end program conversions
