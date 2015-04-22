program write_stream_test
    use, intrinsic :: iso_fortran_env
    implicit none
    integer, parameter :: nr_data = 500, max_len=100
    character(len=max_len) :: file_name = 'array_file.dat'
    integer :: status
    integer, parameter :: file_unit = 9
    character(len=max_len) :: msg = 'OK'
    real(kind=REAL64), dimension(nr_data) :: x

! open file
    open(unit=file_unit, file=file_Name, access='stream', &
         action='write', status='replace', form='unformatted', &
         iostat=status, iomsg=msg)
    if (status /= 0) then
        write (unit=error_unit, fmt="('#error: ', A)") msg
        stop
    end if

! initialize data
    call random_number(x)
    print "('sum = ', E25.15)", sum(x)

! write data
    write (unit=file_unit, iostat=status, iomsg=msg) x
    if (status /= 0) then
        write (unit=error_unit, fmt="('#error: ', A)") msg
        stop
    end if

! close file
    close(unit=file_unit, iostat=status, iomsg=msg)
    if (status /= 0) then
        write (unit=error_unit, fmt="('#error: ', A)") msg
        stop
    end if

end program write_stream_test
