program cli_test
    use, intrinsic :: iso_fortran_env, only : error_unit
    implicit none
    integer, parameter :: arg_count_error = 1, &
                          real_type_error = 2, &
                          integer_type_error = 3
    integer, parameter :: max_len = 1024
    character(len=max_len) :: cla, message
    real :: x
    integer :: i
    character(len=max_len) :: s
    integer :: status, length

! check number of arguments
    if (command_argument_count() /= 3) then
        write (unit=error_unit, fmt='(A)') &
                '# error: expecting at least 3 values'
        stop arg_count_error
    end if

! get first argument, and convert to real
    call get_command_argument(1, cla, length)
    read (cla, fmt='(E25.15)', iostat=status, iomsg=message) x
    if (status /= 0) then
        write (unit=error_unit, fmt='(2A)') &
                '# error: ', trim(message)
        stop real_type_error
    end if
    print *, x

! get second argument, and convert to integer
    call get_command_argument(2, cla, length)
    read (cla, fmt='(I10)', iostat=status, iomsg=message) i
    if (status /= 0) then
        write (unit=error_unit, fmt='(2A)') &
                '# error: ', trim(message)
        stop integer_type_error
    end if
    print *, i

! get third argument
    call get_command_argument(3, s, length)
    print "('|', A, '|')", trim(s)

end program cli_test
