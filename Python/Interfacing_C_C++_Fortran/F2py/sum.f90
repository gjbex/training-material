program compute_sum
    use array_utils
    implicit none
    integer, parameter :: n = 100
    real(kind=8), dimension(:), allocatable :: a
    real(kind=8) :: s
    integer :: i
    allocate(a(n))
    do i = 1, n
        a(i) = 1.0D00*i
    end do
    s = sum_array(a)
    print *, s
    deallocate(a)

end program compute_sum

