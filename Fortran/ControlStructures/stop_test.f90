program stop_test
    use, intrinsic :: iso_fortran_env, only : error_unit
    implicit none
    integer, parameter :: real_type_error = 1
    integer, parameter :: max_len = 1024
    character(len=max_len) :: cla, message
    real :: x
    character(len=max_len) :: s
    integer :: status, length

! check number of arguments
    if (command_argument_count() /= 1) then
        stop 'expecting one argument'
    end if

! get first argument, and convert to real
    call get_command_argument(1, cla, length)
    read (cla, fmt='(E25.15)', iostat=status, iomsg=message) x
    if (status /= 0) then
        write (unit=error_unit, fmt='(A)'), 'argument was not a real number'
        stop real_type_error
    end if
    print *, x

end program stop_test
