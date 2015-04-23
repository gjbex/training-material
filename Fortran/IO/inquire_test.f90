program inquiry_test
    use, intrinsic :: iso_fortran_env, only : error_unit, output_unit
    implicit none
    integer, parameter :: file_unit = 9, max_len = 128, &
                          file_open_err = 1,            &
                          file_read_err = 2,            &
                          file_close_err = 3
    integer :: status, file_pos, i
    logical :: file_exists
    character(len=max_len), parameter :: file_ok = 'inquire_test.f90', &
                                         file_nok = 'blabla.f77'
    character(len=max_len) :: message, file_name
    character :: c

    inquire(file=file_ok, exist=file_exists)
    print '(A20, L)', file_ok, file_exists

    inquire(file=file_nok, exist=file_exists)
    print '(A20, L)', file_nok, file_exists
    
    open (unit=file_unit, file=file_ok, form='formatted', &
          action='read', access='sequential', status='old', &
          iostat=status, iomsg=message)
    if (status /= 0) then
        write (unit=error_unit, fmt="('#error: ', A)") message
        stop file_open_err
    end if

    inquire(unit=file_unit, pos=file_pos)
    print '(A, I0)', 'position after open: ', file_pos

    do i = 1, 10
        read (unit=file_unit, fmt='(A1)', advance='no', &
              iostat=status, iomsg=message) c
        write (unit=output_unit, fmt='(A1)', advance='no') c
        if (status /= 0) then
            write (unit=error_unit, fmt="('#error: ', A)") message
            stop file_read_err
        end if
    end do
    print *, ''

    inquire(unit=file_unit, pos=file_pos)
    print '(A, I0)', 'position after 10 reads: ', file_pos

    inquire(unit=file_unit, name=file_name)
    print '(2A)', 'current file: ', trim(file_name)

    close (unit=file_unit, iostat=status, iomsg=message)
    if (status /= 0) then
        write (unit=error_unit, fmt="('#error: ', A)") message
        stop file_close_err
    end if

end program inquiry_test
