program trace_nan
    use, intrinsic :: iso_fortran_env, only : dp => REAL64
    implicit none
    integer, parameter :: n = 4
    integer :: i
    real(kind=dp), parameter, dimension(n) :: a = [ 1.0_dp, 3.0_dp, &
                                                    -3.0_dp, 5.3_dp ]
    real(kind=dp), dimension(n) :: b

    do i = 1, n
        b(i) = sqrt(a(i))
    end do
    do i = 1, n
        print '(2F10.3)', a(i), b(i)
    end do

end program trace_nan
