program watch
    implicit none
    integer, parameter :: rows = 3, cols = 4
    integer :: i, j
    integer, dimension(rows, cols) :: values
    character(len=32) :: fmt_str

    do j = 1, cols
        do i  = 1, rows
          values(i, j) = (i - 1)*cols + j
        end do
    end do

    write (fmt_str, '(A, I0, A)') '(', cols, 'I4)'
    do i = 1, rows
        print fmt_str, values(i, :)
    end do

end program watch
