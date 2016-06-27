program merge_test
    implicit none
    integer :: i, j, k
    i = 10
    j = merge(-1, 1, i < 15)
    i = 20
    k = merge(-1, 1, i < 15)
    print '(2I5)', j, k
end program merge_test
