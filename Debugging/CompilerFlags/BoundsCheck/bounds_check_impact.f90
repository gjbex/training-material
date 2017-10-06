program array_bounds_check
    implicit none
    integer, parameter :: n = 1000000, nr_searches = 5000
    integer, dimension(n) :: x
    integer :: i, search_nr, nr_found
    do i = 1, n
        x(i) = i
    end do
    nr_found = 0
    do search_nr = 1, nr_searches
        do i = 1, n
            if (x(i) == i) nr_found = nr_found + 1
        end do
    end do
    print '(A, I12)', 'found ', nr_found
end program array_bounds_check
