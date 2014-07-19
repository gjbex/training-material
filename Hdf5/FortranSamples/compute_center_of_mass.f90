program compute_center_of_mass
use, intrinsic :: iso_fortran_env
use hdf5
implicit none
integer, parameter :: sp = REAL32
integer, parameter :: mass_rank = 1, pos_rank = 2
character(len=1024) :: file_name
character(len=50), parameter :: mass_loc = "particles/mass", &
                                pos_loc = "particles/position"
integer(hid_t) :: file_id, mass_dset_id, mass_dspace_id, &
                  pos_dset_id, pos_dspace_id
integer(hsize_t), dimension(mass_rank) :: mass_dim, mass_max_dim
integer(hsize_t), dimension(pos_rank) :: pos_dim, pos_max_dim
integer :: status
real(kind=sp), dimension(:), allocatable :: mass
real(kind=sp), dimension(:, :), allocatable :: pos
real(kind=sp) :: total_mass
real(kind=sp), dimension(:), allocatable :: center_pos
integer :: i

! check whether at least one command line argument was given
if (command_argument_count() < 1) then
    write (unit=error_unit, fmt="(A)") "#error: expecting file name"
    stop
end if
                                   
! get command line argument
call get_command_argument(1, file_name)
file_name = trim(file_name)

! open HDF5 Fortran interface
call h5open_f(status)

! open HDF5 file
call h5fopen_f(file_name, H5F_ACC_RDONLY_F, file_id, status)
if (status /= 0) then
    write (unit=error_unit, fmt="(A, A)") "#error: can not open file ", &
                                          file_name
    stop
end if

! open mass and position dataset
call h5dopen_f(file_id, mass_loc, mass_dset_id, status)
if (status /= 0) then
    write (unit=error_unit, fmt="(A, A)") "#error: can not open dataset ", &
                                          file_name
    stop
end if
call h5dopen_f(file_id, pos_loc, pos_dset_id, status)
if (status /= 0) then
    write (unit=error_unit, fmt="(A, A)") "#error: can not open dataset ", &
                                          file_name
    stop
end if


! get correspoding dataspaces
call h5dget_space_f(mass_dset_id, mass_dspace_id, status)
call h5dget_space_f(pos_dset_id, pos_dspace_id, status)

! find mass and position dimensions
call h5sget_simple_extent_dims_f(mass_dspace_id, mass_dim, mass_max_dim, &
                                 status)
call h5sget_simple_extent_dims_f(pos_dspace_id, pos_dim, pos_max_dim, &
                                 status)

! allocate mass array
allocate(mass(mass_dim(1)))
allocate(pos(pos_dim(1), pos_dim(2)))
allocate(center_pos(pos_dim(1)))

! read mass data
call h5dread_f(mass_dset_id, H5T_NATIVE_REAL, mass, mass_dim, status)
call h5dread_f(pos_dset_id, H5T_NATIVE_REAL, pos, pos_dim, status)

! close mass and position data set
call h5dclose_f(mass_dset_id, status)
call h5dclose_f(pos_dset_id, status)

! close HDF5 file
call h5fclose_f(file_id, status)

! close HDF5 Fortran interface
call h5close_f(status)

! compute center of mass and print it
total_mass = sum(mass)
center_pos(:) = 0.0_sp
do i = 1, pos_dim(2)
    center_pos(:) = center_pos(:) + mass(i)*pos(:, i)
end do
center_pos = center_pos/total_mass
print "(3E15.6)", center_pos

! deallocate mass and pos
deallocate(mass)
deallocate(pos)
deallocate(center_pos)

end program compute_center_of_mass
