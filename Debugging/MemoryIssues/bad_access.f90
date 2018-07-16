program bad_access
    implicit none
    integer, parameter :: default_n = 5
    integer :: i, n, sum
    integer, allocatable, dimension(:) :: a

    if (command_argument_count() == 1) then
        block
            character(len=1024) :: buffer
            call get_command_argument(1, buffer)
            read (buffer, '(I10)') n
        end block
    else
        n = default_n
    end if

    allocate(a(n))
    do i = 1, n
        a(i) = i
    end do

    sum = 0
    do i = n, 0, -1
        sum = sum + a(i)
    end do
    print '(A, I10)', sum

    deallocate(a)

end program bad_access
