program stream_read_write_test
    use, intrinsic :: iso_fortran_env
    implicit none
    integer, parameter :: nr_data = 11, max_len=100
    character(len=max_len) :: file_name = 'stream_file.dat'
    real(kind=REAL64) :: eps
    integer :: i, file_pos, status, dummy
    integer, parameter :: file_unit = 9
    character(len=max_len) :: msg = 'OK'
    real(kind=REAL64) :: x, y

! open file
    open(unit=file_unit, file=file_Name, access='stream', &
         action='readwrite', status='new', form='unformatted', &
         iostat=status, iomsg=msg)
    if (status /= 0) then
        write (unit=error_unit, fmt="('#error: ', A)") msg
        stop
    end if

! write data
    write (unit=file_unit, iostat=status, iomsg=msg) nr_data
    if (status /= 0) then
        write (unit=error_unit, fmt="('#error: ', A)") msg
        stop
    end if

! mark position
    inquire(unit=file_unit, pos=file_pos)
    do i = 1, nr_data
        x = real(i - 1, kind=REAL64)/(nr_data - 1)
        write (unit=file_unit, iostat=status, iomsg=msg) i, x, f(x)
        if (status /= 0) then
            write (unit=error_unit, fmt="('#error: ', A)") msg
            stop
        end if
    end do

! start reading file
    read (unit=file_unit, pos=file_pos, iostat=status, iomsg=msg) &
            dummy, x, y
    eps = abs(y - f(x))/f(x)
    write (unit=output_unit, fmt='(I3, F25.15)') 0, eps
    do i = 2, nr_data
        read (unit=file_unit, iostat=status, iomsg=msg) &
                dummy, x, y
        if (status /= 0) then
            write (unit=error_unit, fmt="('#error: ', A)") msg
            stop
        end if
        eps = abs(y - f(x))/f(x)
        write (unit=output_unit, fmt='(I3, F25.15)') i, eps
    end do

! close file
    close(unit=file_unit, iostat=status, iomsg=msg)
    if (status /= 0) then
        write (unit=error_unit, fmt="('#error: ', A)") msg
        stop
    end if

contains

    real(kind=REAL64) function f(x)
        implicit none
        real(Kind=REAL64), intent(in) :: x
        f = sqrt(x)
    end function f

end program stream_read_write_test
