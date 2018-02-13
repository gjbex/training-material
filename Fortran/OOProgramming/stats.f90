program stats_test
    use, intrinsic :: iso_fortran_env, only : f8 => REAL64
    use :: stats_mod
    implicit none
    integer, parameter :: n = 10
    integer :: i
    real(kind=f8), dimension(n) :: data = [ ((0.5_f8*i), i = 1, n) ]
    type(stats_type) :: my_stats
    my_stats = new_stats()
    do i = 1, n
        call my_stats%add(data(i))
    end do
    print '(A, F10.2)', 'average =', my_stats%avg()
end program stats_test
