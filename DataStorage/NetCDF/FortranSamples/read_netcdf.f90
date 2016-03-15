program read_netcdf
use netcdf
use real_types
use grid
implicit none
character(len=1024) :: file_name
integer :: ret_val, nc_id, i, j, k
integer, dimension(3) :: dims
real(kind=sp), dimension(:), allocatable :: x, y, z
real(kind=sp), dimension(:,:,:), allocatable :: value
real(kind=sp) :: v, max_diff

! get file name specified as command line argument
if (command_argument_count() /= 1) then
    print *, "### error: expecting file name"
    stop
end if
call get_command_argument(1, file_name)

! open NetCDF file for reading
ret_val = nf90_open(file_name, NF90_NOWRITE, nc_id)
if (ret_val /= nf90_noerr) then
    print *, "### error: file open failed"
    stop
end if

! get the x-, y-, and z-grid coordinates
call grid_axis(nc_id, "x", x)
call grid_axis(nc_id, "y", y)
call grid_axis(nc_id, "z", z)

! get the values
call grid_3d_data(nc_id, "value", value)

dims = shape(value)

max_diff = 0.0_sp
do i = 1, dims(1)
    do j = 1, dims(2)
        do k = 1, dims(3)
            v = exp(-(x(i)**2 + y(j)**2 +z(k)**2))
            max_diff = max(abs(v - value(i, j, k)), max_diff)
        end do
    end do
end do
print *, "maximum difference = ", max_diff

! close NetCDF file
ret_val = nf90_close(nc_id)
if (ret_val /= nf90_noerr) then
    print *, "### error: file close failed"
    stop
end if

! deallocate arrays
deallocate(x)
deallocate(y)
deallocate(z)

end program read_netcdf
