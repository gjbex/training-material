program unallocated
    use, intrinsic :: iso_fortran_env, only : error_unit
    implicit none 
    integer :: n, i
    real, dimension(:), allocatable :: data
    real :: r
    character(len=80) :: buffer

    if (command_argument_count() < 1) then
        write (fmt='(A)', unit=error_unit) &
            'missing command argument, positive integer expected'
        stop 1
    end if
    call get_command_argument(1, buffer)
    read (buffer, fmt='(I10)') n
    do i = 1, n
        call random_number(r)
        data(i) = r
    end do
    print '(A, F15.5)', sum(data)
end program unallocated
