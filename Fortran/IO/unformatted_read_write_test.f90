program unformatted_read_write_test
    use, intrinsic :: iso_fortran_env
    implicit none
    integer, parameter :: nr_data = 11, max_len=100
    character(len=max_len) :: file_name = 'bin_file.dat'
    real(kind=REAL64), dimension(:), allocatable :: x, y
    real(kind=REAL64) :: eps
    integer :: i

    call write_file(file_name, nr_data)
    call read_file(file_name, x, y)
    do i = 1, nr_data
        eps = abs(y(i) - f(x(i)))/f(x(i))
        write (unit=output_unit, fmt='(I3, F25.15)') i, eps
    end do
    deallocate(x)
    deallocate(y)

contains

    subroutine write_file(file_name, nr_data)
        implicit none
        character(len=*), intent(in) :: file_name
        integer, intent(in) :: nr_data
        integer, parameter :: file_unit = 9, max_len = 100
        integer :: i, status
        character(len=max_len) :: msg = 'OK'
        real(kind=REAL64) :: x

        open(unit=file_unit, file=file_Name, access='sequential', &
             action='write', status='new', form='unformatted', &
             iostat=status, iomsg=msg)
        if (status /= 0) then
            write (unit=error_unit, fmt="('#error: ', A)") msg
            stop
        end if
        write (unit=file_unit, iostat=status, iomsg=msg) nr_data
        if (status /= 0) then
            write (unit=error_unit, fmt="('#error: ', A)") msg
            stop
        end if
        do i = 1, nr_data
            x = real(i - 1, kind=REAL64)/(nr_data - 1)
            write (unit=file_unit, iostat=status, iomsg=msg) i, x, f(x)
            if (status /= 0) then
                write (unit=error_unit, fmt="('#error: ', A)") msg
                stop
            end if
        end do
        close(unit=file_unit, iostat=status, iomsg=msg)
        if (status /= 0) then
            write (unit=error_unit, fmt="('#error: ', A)") msg
            stop
        end if

    end subroutine write_file

    subroutine read_file(file_name, x, y)
        implicit none
        character(len=*), intent(in) :: file_name
        real(kind=REAL64), dimension(:), allocatable, intent(inout) :: x, y
        integer, parameter :: file_unit = 9, max_len = 100
        integer :: nr_data, status, i, dummy
        character(len=max_len) :: msg = 'OK'

        open(unit=file_unit, file=file_Name, access='sequential', &
             action='read', status='old', form='unformatted', &
             iostat=status, iomsg=msg)
        if (status /= 0) then
            write (unit=error_unit, fmt="('#error: ', A)") msg
            stop
        end if
        read (unit=file_unit, iostat=status, iomsg=msg) nr_data
        allocate(x(nr_data), stat=status)
        if (status /= 0) then
            write (unit=error_unit, fmt="('#error: ', A)") &
                    'can not allocate x'
            stop
        end if
        allocate(y(nr_data), stat=status)
        if (status /= 0) then
            write (unit=error_unit, fmt="('#error: ', A)") &
                    'can not allocate y'
            stop
        end if
        do i = 1, nr_data
            read (unit=file_unit, iostat=status, iomsg=msg) &
                    dummy, x(i), y(i)
            if (status /= 0) then
                write (unit=error_unit, fmt="('#error: ', A)") msg
                stop
            end if
        end do
        close(unit=file_unit, iostat=status, iomsg=msg)
        if (status /= 0) then
            write (unit=error_unit, fmt="('#error: ', A)") msg
            stop
        end if
    end subroutine read_file

    real(kind=REAL64) function f(x)
        implicit none
        real(Kind=REAL64), intent(in) :: x
        f = sqrt(x)
    end function f

end program unformatted_read_write_test
