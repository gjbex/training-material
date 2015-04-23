program append_test
    use, intrinsic :: iso_fortran_env, only : error_unit, dp => REAL64
    implicit none
    integer, parameter :: file_unit = 9, max_len = 128, &
                          file_open_err = 1,  &
                          file_write_err = 2, &
                          file_pos_err = 3,   &
                          file_read_err = 4,  &
                          file_close_err = 5
    character(len=max_len), parameter :: file_name = 'data.txt'
    integer :: status, i, file_pos, file_end_pos
    real(kind=dp), parameter :: x_delta = 0.1
    real(kind=dp) :: x, y
    character(len=max_len) :: message

! open file for read/write
    open (unit=file_unit, file=file_name, access='stream', &
          action='readwrite', status='replace', form='formatted', &
          iostat=status, iomsg=message)
    if (status /= 0) then
        write (unit=error_unit, fmt="('#error: ', A)") message
        stop file_open_err
    end if

! write some data
    x = 0.0_dp
    do i = 0, 10
        write (unit=file_unit, fmt='(2F10.4)', &
               iostat=status, iomsg=message) x, sqrt(x)
        if (status /= 0) then
            write (unit=error_unit, fmt="('#error: ', A)") message
            stop file_write_err
        end if
        x = x + x_delta
    end do
    inquire(unit=file_unit, pos=file_end_pos)

! rewind file
    inquire(unit=file_unit, pos=file_pos)
    print '(A, I0)', 'position before rewind: ', file_pos
    rewind(unit=file_unit, iostat=status, iomsg=message)
    if (status /= 0) then
        write (unit=error_unit, fmt="('#error: ', A)") message
        stop file_pos_err
    end if
    inquire(unit=file_unit, pos=file_pos)
    print '(A, I0)', 'position after rewind: ', file_pos

! read some data
    do i = 0, 3
        read (unit=file_unit, fmt='(2F10.4)', advance='yes', &
              iostat=status, iomsg=message) x, y
        if (status /= 0) then
            write (unit=error_unit, fmt="('#error: ', A)") message
            stop file_read_err
        end if
        print '(F3.1, E15.4)', x, abs(sqrt(x) - y)
    end do

    backspace(unit=file_unit)
    read (unit=file_unit, fmt='(2F10.4)', advance='yes', &
          iostat=status, iomsg=message) x, y
    if (status /= 0) then
        write (unit=error_unit, fmt="('#error: ', A)") message
        stop file_read_err
    end if
    print '(A, F3.1, E15.4)', 'reread: ', x, abs(sqrt(x) - y)

    x = 1.1_dp
    write (unit=file_unit, pos=file_end_pos, fmt='(2F10.4)', &
           iostat=status, iomsg=message) x, sqrt(x)
    do i = 11, 15
        write (unit=file_unit, fmt='(2F10.4)', &
               iostat=status, iomsg=message) x, sqrt(x)
        if (status /= 0) then
            write (unit=error_unit, fmt="('#error: ', A)") message
            stop file_write_err
        end if
        x = x + x_delta
    end do

! close file
    close(unit=file_unit, iostat=status, iomsg=message)
    if (status /= 0) then
        write (unit=error_unit, fmt="('#error: ', A)") message
        stop file_close_err
    end if

end program append_test
