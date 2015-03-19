program append_h5
use, intrinsic :: iso_fortran_env
use hdf5
implicit none
integer, parameter :: sp = REAL32
integer, parameter :: pos_space_rank = 3, pos_rank = 2, nr_pos = 10
character(len=3) :: dset_name = "pos"
character(len=1024) :: file_name
logical :: file_exists
integer :: status
integer(hid_t) :: file_id, dset_id, dspace_id, all_dspace_id, &
                  dset_prop_id, fspace_id
integer(hsize_t), dimension(pos_rank) :: pos_dim, max_pos_dim, &
                                         pos_chunk_dim, pos_offset, &
                                         new_pos_dim
real(kind=sp), dimension(pos_space_rank, nr_pos) :: data
integer :: i, j

! get file name from command line arguments
if (command_argument_count() /= 1) then
    write (unit=error_unit, fmt="(A)") "#error: no file name given"
    stop
end if
call get_command_argument(1, file_name)

! open HDF5 Fortran interface
call h5open_f(status)

! check whether file exists
inquire(file=file_name, exist=file_exists)
if (file_exists) then
    ! open HDF5 file
    call h5fopen_f(trim(file_name), H5F_ACC_RDWR_F, file_id, status)
else
    ! create new file
    call h5fcreate_f(trim(file_name), H5F_ACC_TRUNC_F, file_id, status)
end if
! open dataset
call h5dopen_f(file_id, dset_name, dset_id, status)
! if dataset doesn't exist, create it
if (status < 0) then
    if (.not. file_exists) then
        ! set dimenions and create filespace
        pos_dim(1) = pos_space_rank
        pos_dim(2) = 0
        max_pos_dim(1) = pos_space_rank
        max_pos_dim(2) = H5S_UNLIMITED_F
        call h5screate_simple_f(pos_rank, pos_dim, fspace_id, status, &
                                max_pos_dim)
        ! set chunk sizes and create dataset 
        pos_chunk_dim(1) = pos_space_rank
        pos_chunk_dim(2) = nr_pos
        call h5pcreate_f(H5P_DATASET_CREATE_F, dset_prop_id, status)
        call h5pset_chunk_f(dset_prop_id, pos_rank, pos_chunk_dim, status)
        ! create dataset
        call h5dcreate_f(file_id, dset_name, H5T_NATIVE_REAL, &
                         fspace_id, dset_id, status, dset_prop_id)
        if (status /= 0) then
            write(unit=error_unit, fmt="(3A)") "#error: can not create '", &
                                               trim(dset_name), "'"
            stop
        end if
        ! close property and filespace
        call h5pclose_f(dset_prop_id, status)
        call h5sclose_f(fspace_id, status)
    else
        write(unit=error_unit, fmt="(A)") "#error: file was not created with append_h5"
        stop
    end if
end if
! get filespace, get current dimensions and close filespace
call h5dget_space_f(dset_id, fspace_id, status)
call h5sget_simple_extent_dims_f(fspace_id, pos_dim, max_pos_dim, status)
call h5sclose_f(fspace_id, status)

! extend data set to accomodate new data, and close it
new_pos_dim(1) = pos_dim(1)
new_pos_dim(2) = nr_pos + pos_dim(2)
call h5dextend_f(dset_id, new_pos_dim, status)
call h5dclose_f(dset_id, status)

! compute data
do j = 1, nr_pos
    do i = 1, pos_space_rank
        data(i, j) = 1.0_sp*i*j + pos_dim(2)
    end do
end do

! create a hyperslab
pos_offset(1) = 0
pos_offset(2) = pos_dim(2)
pos_chunk_dim(1) = pos_space_rank
pos_chunk_dim(2) = nr_pos
call h5dopen_f(file_id, dset_name, dset_id, status)
call h5dget_space_f(dset_id, fspace_id, status)
call h5sselect_hyperslab_f(fspace_id, H5S_SELECT_SET_F, pos_offset, &
                           pos_chunk_dim, status)
call h5screate_simple_f(pos_rank, pos_chunk_dim, dspace_id, status)
! write data to HDF5 file
call h5dwrite_f(dset_id, H5T_NATIVE_REAL, data, pos_chunk_dim, status, &
                mem_space_id=dspace_id, file_space_id=fspace_id)

! close filespace, dataset
call h5sclose_f(fspace_id, status)
call h5sclose_f(dspace_id, status)
call h5dclose_f(dset_id, status)

! close HDF% file
call h5fclose_f(file_id, status)

! close HDF5 Fortran interface
call h5close_f(status)

end program append_h5
