program array_bounds_check
    implicit none
    integer, parameter :: n = 1000, nr_searches = 500000000
    integer, dimension(n) :: x
    integer :: i, search_nr, nr_found
    real :: r
    do i = 1, n
        x(i) = i
    end do
    nr_found = 0
    do search_nr = 1, nr_searches
        call random_number(r)
        i = 1 + int(r*n)
        if (x(i) == i) nr_found = nr_found + 1
    end do
    print '(A, I12)', 'found ', nr_found
end program array_bounds_check
