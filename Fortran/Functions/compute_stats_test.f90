program compute_stats_test
    use, intrinsic :: iso_fortran_env
    implicit none
    integer, parameter :: sp = REAL32
    real(kind=sp), dimension(10) :: v
    real(kind=sp) :: mean, stddev
    call init_vector(v)
    call compute_stats(v, mean, stddev)
    print *, mean, stddev

contains

    subroutine init_vector(v)
        implicit none
        real(kind=sp), dimension(:), intent(inout) :: v
        integer :: i
        do i = 1, size(v)
            v(i) = real(i, kind=sp)
        end do
    end subroutine init_vector

    subroutine compute_stats(v, mean, stddev)
        implicit none
        real(kind=sp), dimension(:), intent(in) :: v
        real(kind=sp), intent(out) :: mean, stddev
        real(kind=sp) :: s, s2
        integer :: n
        n = size(v)
        s = sum(v)
        s2 = sum(v*v)
        mean = s/n
        stddev = sqrt((s*s - s2)/(n - 1))
    end subroutine compute_stats

end program compute_stats_test
