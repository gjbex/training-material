program create_h5
use hdf5
use, intrinsic :: iso_fortran_env
implicit none
integer, parameter :: sp = REAL32
character(len=1024) :: file_name
character(len=20), parameter :: group_name = "particles", &
                                mass_dset_name = "mass", &
                                pos_dset_name = "position"
integer(hid_t) :: file_id, group_id, mass_dset_id, mass_dspace_id, &
                  pos_dset_id, pos_dspace_id
integer, parameter :: nr_particles = 10
integer, parameter :: mass_rank = 1, pos_rank = 2, pos_space_rank = 3
integer(hsize_t), dimension(mass_rank) :: mass_dim = [ nr_particles ]
integer(hsize_t), dimension(pos_rank) :: pos_dim = [ pos_space_rank, &
                                                     nr_particles ]
integer :: error
real(kind=sp), dimension(nr_particles) :: mass
real(kind=sp), dimension(pos_space_rank, nr_particles) :: pos
integer :: i, j
real(kind=sp) :: r

! compute data, i.e., particle masses and positions
do i = 1, nr_particles
    call random_number(mass(i))
    do j = 1, pos_space_rank
        call random_number(r)
        pos(j, i) = 2.0_sp*(r - 0.5_sp)
    end do
end do

! get file name from command line
if (command_argument_count() < 1) then
    write (unit=error_unit, fmt="(A)") "# error: no file name given"
    stop
end if
call get_command_argument(1, file_name)
file_name = trim(file_name)

! initialize Fortran interface
call h5open_f(error)

! open the HDF5 file, overwriting it if it alread exists
call h5fcreate_f(file_name, H5F_ACC_TRUNC_F, file_id, error)
if (error /= 0) then
    write (unit=error_unit, fmt="(A, A)") "# error opening file ", &
                                          file_name
    stop
end if

! create a group at the root-level
call h5gcreate_f(file_id, group_name, group_id, error)

! create the mass and position dataspaces
call h5screate_simple_f(mass_rank, mass_dim, mass_dspace_id, error)
call h5screate_simple_f(pos_rank, pos_dim, pos_dspace_id, error)

! create the mass and position datasets
call h5dcreate_f(group_id, mass_dset_name, H5T_NATIVE_REAL, &
                 mass_dspace_id, mass_dset_id, error)
call h5dcreate_f(group_id, pos_dset_name, H5T_NATIVE_REAL, &
                 pos_dspace_id, pos_dset_id, error)

! write mass and position data
call h5dwrite_f(mass_dset_id, H5T_NATIVE_REAL, mass, mass_dim, error)
call h5dwrite_f(pos_dset_id, H5T_NATIVE_REAL, pos, pos_dim, error)

! close mass and position data sets
call h5dclose_f(mass_dset_id, error)
call h5dclose_f(pos_dset_id, error)

! close mass and position data spaces
call h5sclose_f(mass_dspace_id, error)
call h5sclose_f(pos_dspace_id, error)

! close group
call h5gclose_f(group_id, error)

! close HDF5 file
call h5fclose_f(file_id, error)

! finalize Fortran HDF5 interface
call h5close_f(error)

end program create_h5

