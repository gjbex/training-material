program read_stream_test
    use, intrinsic :: iso_fortran_env
    implicit none
    integer, parameter :: max_len=100
    character(len=max_len) :: file_name = 'array_file.dat'
    integer :: status
    integer, parameter :: file_unit = 9
    character(len=max_len) :: msg = 'OK'
    real(kind=REAL64) :: x, total

! open file
    open(unit=file_unit, file=file_Name, access='stream', &
         action='read', status='old', form='unformatted', &
         iostat=status, iomsg=msg)
    if (status /= 0) then
        write (unit=error_unit, fmt="('#error: ', A)") msg
        stop
    end if

! initialize data
    total = 0.0_REAL64

! read data
    do while (.true.)
        read (unit=file_unit, iostat=status, iomsg=msg) x
        if (status == iostat_end) then
            exit
        else if (status /= 0) then
            write (unit=error_unit, fmt="('#error: ', A)") msg
            stop
        end if
        total = total + x
    end do

! close file
    close(unit=file_unit, iostat=status, iomsg=msg)
    if (status /= 0) then
        write (unit=error_unit, fmt="('#error: ', A)") msg
        stop
    end if

! print sum
    print "('sum = ', E25.15)", total

end program read_stream_test
