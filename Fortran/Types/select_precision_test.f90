program select_precision_test
    implicit none
    integer, parameter :: sp = selected_real_kind(p=6, r=30), &
                          dp = selected_real_kind(p=12, r=100), &
                          int = selected_int_kind(r=8), &
                          long = selected_int_kind(r=12)
    real(kind=sp) :: x
    real(kind=dp) :: y
    integer(Kind=int) :: m
    integer(Kind=long) :: n

    x = 1.0_sp/3.0_sp
    y = 1.0_dp/3.0_dp
    print *, x, y
    print *, sp, dp

    m = 2_int**30_int
    n = 2_long**40_long
    print *, m, n
    print *, int, long

end program select_precision_test
