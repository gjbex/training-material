program rand_test
    use, intrinsic :: iso_fortran_env, only : sp => REAL32, dp => REAL64
    use random_mod, only : random_normal_number
    implicit none
    integer, parameter :: N = 10000
    real(kind=dp) :: r
    integer :: i

    do i = 1, N
        call random_normal_number(r)
        print *, r
    end do

end program rand_test
