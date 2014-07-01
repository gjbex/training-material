program data_reader
    use, intrinsic :: iso_fortran_env
    implicit none
    integer :: x_points = 10, y_points = 10, z_points = 10
    real(kind=REAL32), parameter :: x_delta = 1.0e-1, &
                                    y_delta = 1.0e-1, &
                                    z_delta = 1.0e-1
    real(kind=REAL32) :: x = 0.0, y = 0.0, z = 0.0, val
    integer :: i, j, k
    integer :: istat = 0
    character(len=40) :: buffer

    if (command_argument_count() == 3) then
        call get_command_argument(1, buffer)
        read (unit=buffer, fmt='(I4)') x_points
        call get_command_argument(2, buffer)
        read (unit=buffer, fmt='(I4)') y_points
        call get_command_argument(3, buffer)
        read (unit=buffer, fmt='(I4)') z_points
    end if
    open(unit=1, file='data.bin', form='unformatted', &
         access='stream', iostat=istat)
    if (istat /= 0) then
        print *, '# error: I/O error: can not open'
        stop
    end if
    x = 0.0
    do i = 1, x_points
        y = 0.0
        do j = 1, y_points
            z = 0.0
            do k = 1, z_points
                read(unit=1) val
                print *, x, y, z, val
                z = z + z_delta
            end do
            y = y + y_delta
        end do
        x = x + x_delta
    end do
    close(unit=1)

end program data_reader
