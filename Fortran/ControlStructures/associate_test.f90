program block_test
    implicit none
    integer, parameter :: n = 3
    integer :: i
    integer, dimension(n, n) :: a = reshape( [ (i, i = 1, n*n) ], [n, n] )

    print '(A)', 'block'
    do i = 1, n
        block
            integer, dimension(n) :: row
            row = a(:, i)
            print '(A25, 5I4)', 'row: ', row
            row(1) = 123
            print '(A25, 3I4)', 'row after update: ', row
            print '(A25, 3I4)', 'matrix after update: ', a(:, i)
        end block
    end do
    print '(A)', 'associate'
    do i = 1, n
        associate( row => a(:, i) )
            print '(A25, 5I4)', 'row: ', row
            row(1) = 123
            print '(A25, 3I4)', 'row after update: ', row
            print '(A25, 3I4)', 'matrix after update: ', a(:, i)
        end associate
    end do
end program block_test
