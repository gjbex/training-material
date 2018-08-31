program command_line_trouble
    use, intrinsic :: iso_fortran_env, only : error_unit
    implicit none
    integer :: n, ierr
    real :: x
    character(len=80) :: buffer, msg
    if (command_argument_count() /= 2) then
        write (unit=error_unit, fmt='(A)') &
            '### error: expecting integer and real as argument'
        stop 1
    end if
    call get_command_argument(1, buffer)
    read (buffer, fmt='(I10)') n
    call get_command_argument(2, buffer)
    read (buffer, fmt='(F25.16)', iostat=ierr, iomsg=msg) x
    if (ierr /= 0) then
        write (unit=error_unit, fmt='(4A)') &
            '### error: can not convert to real: ', trim(buffer), &
            ', ', trim(msg)
        stop 2
    end if
    print '(A, I10, F25.16)', 'read ', n, x
end program command_line_trouble
