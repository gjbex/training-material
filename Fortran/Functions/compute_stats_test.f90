program compute_stats_test
    use, intrinsic :: iso_fortran_env, only : sp => REAL32
    implicit none
    type stats_type
        real(kind=sp) :: sum, mean, stddev
        integer :: n
    end type stats_type
    type(stats_type) :: stats
    integer, parameter :: data_size = 10
    real(kind=sp), dimension(data_size) :: v
    real(kind=sp) :: mean, stddev
    call init_vector(v)
    call compute_stats(v, mean, stddev)
    print '(2(A14, F10.5))', 'mean = ', mean, 'stddev = ', stddev
    stats = compute_stats_alt(v)
    print '(2(A14, F10.5))', 'mean = ', mean, 'stddev = ', stddev

contains

    subroutine init_vector(v)
        implicit none
        real(kind=sp), dimension(:), intent(inout) :: v
        integer :: i
        v = [ (real(i, kind=sp), i = 1, size(v)) ]
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

    function compute_stats_alt(v) result(stats)
        implicit none
        real(kind=sp), dimension(:), intent(in) :: v
        type(stats_type) :: stats
        real(kind=sp) :: sum2
        stats%n = size(v)
        stats%sum = sum(v)
        sum2 = sum(v**2)
        stats%mean = stats%sum/stats%n
        stats%stddev = sqrt((stats%sum**2 - sum2)/(stats%n - 1))
    end function compute_stats_alt
    
end program compute_stats_test
