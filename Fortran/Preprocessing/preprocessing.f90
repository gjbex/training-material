program preprocessing
implicit none
integer, parameter :: n = 5
integer :: i

do i = 1, n
    print '(A, I0)', 'hello ', i
end do

#ifdef SAY_BYE
do i = 1, n
    print '(A, I0)', 'bye ', i
end do
#endif

end program preprocessing
