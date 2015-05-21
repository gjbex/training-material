program complex_test
    use, intrinsic :: iso_fortran_env, only : REAL32, REAL64
    implicit none
    complex :: z_default
    complex(kind=real32) :: z_32
    complex(kind=real64) :: z_64

    print *, kind(z_default), kind(z_32), kind(z_64)

end program complex_test
