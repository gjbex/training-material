program merge_test
    implicit none
    integer, parameter :: n = 2
    integer :: i, j, k
    real, dimension(n, n) :: a = reshape( [ (1, i = 1, n*n) ], [n, n] ), &
                             b = reshape( [ (5, i = 1, n*n) ], [n, n] ), &
                             c = reshape( [ (i, i = 1, n*n) ], [n, n] ), &
                             d
    i = 10
    j = merge(-1, 1, i < 15)
    i = 20
    k = merge(-1, 1, i < 15)
    print '(2I5)', j, k
    d = merge(a, b, c <= 2)
    print *, c
    print *, d
end program merge_test
