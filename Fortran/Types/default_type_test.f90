program precision_test
    use, intrinsic :: iso_fortran_env, only : REAL32, REAL64
    implicit none
    real :: var
    integer, parameter :: sp = kind(1.0), &
                          dp = selected_real_kind(2*precision(1.0_sp))

    var = 1.0
    print *, "sp = ", sp
    print *, "dp = ", dp
    print *, "REAL = ", kind(var)

    print *, "REAL32 = ", REAL32
    print *, "REAL64 = ", REAL64

end program precision_test

