program deallocating
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
    do i = n, 1, -1
        sum = sum + a(i)
    end do
    print '(A, I10)', sum

    deallocate(a)

    print '(A, I10)', compute_sum(a)

contains

    integer function compute_sum(a)
        implicit none
        integer, dimension(:), intent(in) :: a
        integer :: i, total
        total = 0
        do i = 1, size(a)
            total = total + a(i)
        end do
        compute_sum = total
    end function compute_sum

end program deallocating
