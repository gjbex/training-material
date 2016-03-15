module grid
    use real_types
    use netcdf
    implicit none
    private
    public :: grid_axis
    public :: grid_3d_data

contains

    subroutine grid_axis(nc_id, name, axis)
        implicit none
        integer, intent(in) :: nc_id
        character(len=*), intent(in) :: name
        real(kind=sp), dimension(:), allocatable, intent(out) :: axis
        integer :: var_id, nr_dims, dim
        integer, dimension(NF90_MAX_VAR_DIMS) :: dim_ids
        integer :: ret_val
! retrieve variable ID for given variable name
        ret_val = nf90_inq_varid(nc_id, name, var_id)
        if (ret_val /= nf90_noerr) then
            print "('# err: retrieving ', A, ' var ID failed')", &
                  name
            stop
        end if
! retrieve number of dimensions for variable
        ret_val = nf90_inquire_variable(nc_id, var_id, ndims=nr_dims)
        if (ret_val /= nf90_noerr) then
            print "('# err: retrieving ', A, ' var dimensions failed')", &
                  name
            stop
        end if
! retrieve dimension IDs for variable
        ret_val = nf90_inquire_variable(nc_id, var_id, &
                                        dimids=dim_ids(:nr_dims))
        if (ret_val /= nf90_noerr) then
            print "('# err: retrieving ', A, ' var dim IDs failed')", &
                  name
            stop
        end if
! retrieve variable dimension for variable ID
        ret_val = nf90_inquire_dimension(nc_id, dim_ids(1), len=dim)
        if (ret_val /= nf90_noerr) then
            print "('# err: retrieving ', A, ' var dim failed')", &
                  name
            stop
        end if
! allocate grid axis
        allocate(axis(dim))
! get variable values
        ret_val = nf90_get_var(nc_id, var_id, axis)
        if (ret_val /= nf90_noerr) then
            print "('# err: retrieving ', A, ' values failed')", &
                  name
            stop
        end if
    end subroutine grid_axis

    subroutine grid_3d_data(nc_id, name, data)
        implicit none
        integer, intent(in) :: nc_id
        character(len=*), intent(in) :: name
        real(kind=sp), dimension(:,:,:), allocatable, intent(out) :: data
        integer :: var_id, nr_dims, i
        integer, dimension(3) :: dim_ids, dims
        integer :: ret_val
! retrieve variable ID for given variable name
        ret_val = nf90_inq_varid(nc_id, name, var_id)
        if (ret_val /= nf90_noerr) then
            print "('# err: retrieving ', A, ' var ID failed')", &
                  name
            stop
        end if
! retrieve number of dimensions for variable
        ret_val = nf90_inquire_variable(nc_id, var_id, ndims=nr_dims)
        if (ret_val /= nf90_noerr) then
            print "('# err: retrieving ', A, ' var dimensions failed')", &
                  name
            stop
        end if
        if (nr_dims /= 3) then
            print "('# err: ', A, ' is not a 3D variable')", name
            stop
        end if
! retrieve dimension IDs for variable
        ret_val = nf90_inquire_variable(nc_id, var_id, dimids=dim_ids)
        if (ret_val /= nf90_noerr) then
            print "('# err: retrieving ', A, ' var dim IDs failed')", &
                  name
            stop
        end if
! retrieve variable dimension for variable ID
        do i = 1, 3
            ret_val = nf90_inquire_dimension(nc_id, dim_ids(i), len=dims(i))
            if (ret_val /= nf90_noerr) then
                print "('# err: retrieving ', A, ' var dim failed')", &
                      name
                stop
            end if
        end do
! allocate grid axis
        allocate(data(dims(1), dims(2), dims(3)))
! get variable values
        ret_val = nf90_get_var(nc_id, var_id, data)
        if (ret_val /= nf90_noerr) then
            print "('# err: retrieving ', A, ' values failed')", &
                  name
            stop
        end if
    end subroutine grid_3d_data

end module grid
