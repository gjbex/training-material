program data_creator
    use, intrinsic :: iso_fortran_env
    implicit none
    integer, parameter :: sp=REAL32
    integer :: x_points = 10, y_points = 10, z_points = 10, &
               time_points = 5
    real(kind=sp), parameter :: x_delta = 0.1_sp, &
                                y_delta = 0.1_sp, &
                                z_delta = 0.1_sp, &
                                f_alpha = 0.7_sp
    real(kind=sp) :: x = 0.0_sp, y = 0.0_sp, z = 0.0_sp, alpha = 1.0_sp, &
                     value
    integer :: i, j, k, t
    integer :: istat = 0
    character(len=40) :: buffer
    character(len=1024) :: base_file_name
    character(len=128) :: file_name_fmt = "(A, '-', I0.3, '.bin')"
    character(len=2014) :: file_name

    if (command_argument_count() >= 1) then
        call get_command_argument(1, base_file_name)
    else
        base_file_name = 'data'
    end if
    if (command_argument_count() >= 2) then
        call get_command_argument(2, buffer)
        read (unit=buffer, fmt='(I4)') x_points
        y_points = x_points
        z_points = x_points
    end if
    if (command_argument_count() >= 3) then
        call get_command_argument(2, buffer)
        read (unit=buffer, fmt='(I4)') time_points
    end if
    do t = 1, time_points
        write (unit=file_name, fmt=file_name_fmt) trim(base_file_name), t
        open(unit=1, file=file_name, form='unformatted', &
             access='stream', iostat=istat)
        if (istat /= 0) then
            print *, '# error: I/O error: can not open'
            stop
        end if
        x = 0.0_sp
        do i = 1, x_points
            y = 0.0_sp
            do j = 1, y_points
                z = 0.0_sp
                do k = 1, z_points
                    value = exp(-alpha*(x**2 + y**2 + z**2))
                    write(unit=1) value
                    z = z + z_delta
                end do
                y = y + y_delta
            end do
            x = x + x_delta
        end do
        alpha = alpha * f_alpha
        close(unit=1)
    end do

end program data_creator
