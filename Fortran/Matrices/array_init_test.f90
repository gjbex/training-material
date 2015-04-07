program array_init_test
    implicit none
    integer, parameter :: m = 4, n = 5, p = m*n/2
    integer :: i, j
    integer, dimension(m, n) :: a = reshape( [ (i, i = 1, m*n) ], [m, n])
    real, dimension(m, n) :: b
    integer, dimension(p) :: c
    character(len=10) :: fmt_str

    print '(A)', '# initialized at declaration'
    write (fmt_str, '(A, I1, A)') '(', n, 'I3)'
    do i = 1, size(a, 1)
        print fmt_str, a(i, :)
    end do

    print '(A)', '# initialized in program'
    b = reshape([ ((1.0/(i*n + j), i = 1, m), j=1, n) ], [m, n])
    write (fmt_str, '(A, I1, A)') '(', n, 'F7.3)'
    do i = 1, size(b, 1)
        print fmt_str, b(i, :)
    end do

    print '(A)', '# transposed and reshaped'
    c = reshape(transpose(a(2:3, :)), [p])
    write (fmt_str, '(A, I2, A)') '(', p, 'I3)'
    print fmt_str, c(:)
    
end program array_init_test
