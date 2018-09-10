program file_error
    use, intrinsic :: iso_fortran_env, only : error_unit
    implicit none
    integer, parameter :: read_unit = 20
    real, parameter :: default_alpha = 0.3, default_beta = 0.7
    real :: alpha, beta, value
    character(len=1024) :: file_name, msg, name
    integer :: ierr, line_nr
    
    alpha = default_alpha
    beta = default_beta
    if (command_argument_count() == 1) then
        call get_command_argument(1, file_name)
    else
        write (unit=error_unit, fmt='(A)') &
            '### error: file name expected as argument'
        stop 1
    end if
    open (unit=read_unit, file=trim(file_name), access='sequential', &
          action='read', status='old', form='formatted', &
          iostat=ierr, iomsg=msg)
#ifdef HANDLE_ERRORS
    if (ierr /= 0) then
        write (unit=error_unit, fmt='(3A)') &
            '### error: can not open file ', trim(file_name), &
            ', error: ' // trim(msg)
        stop 1
    end if
#endif
    line_nr = 0
    do
        read (unit=read_unit, fmt="(A10, E25.16)", &
              iostat=ierr, iomsg=msg) name, value
        line_nr = line_nr + 1
        if (ierr < 0) then
            exit
        else if (ierr > 0) then
            write (unit=error_unit, fmt='(A, I3, A)') &
                '### error duing read at line ', line_nr, &
                ': ' // trim(msg)
            stop 2
        end if
        if (trim(name) == 'alpha') then
            alpha = value
        else if (trim(name) == 'beta') then
            beta = value
        else
            write (unit=error_unit, fmt='(A)') &
                '### error: invalid parameter name ' // trim(name)
            stop 3
        end if
    end do
    close (unit=read_unit)

    print '(2(A, E25.16))', 'alpha = ', alpha, ', beta = ', beta

end program file_error
