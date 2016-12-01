program views
    use :: iso_fortran_env, only : error_unit
    use :: mpi_f08
    implicit none
    integer, parameter :: file_name_lenght = 1024, nr_chars = 5, &
                          nr_dims = 1
    integer :: my_rank, my_size, root, i
    integer, dimension(nr_dims) :: sizes, subsizes, starts
    character(len=file_name_lenght) :: file_name
    type(MPI_File) :: file_handle
    type(MPI_Status) :: status
    type(MPI_Datatype) :: file_view
    integer(kind=MPI_OFFSET_KIND) :: disp
    character(len=1) :: buffer

    call mpi_init()
    call mpi_comm_size(MPI_COMM_WORLD, my_size)
    call mpi_comm_rank(MPI_COMM_WORLD, my_rank)
    root = 0
    if (my_rank == root) then
        if (command_argument_count() /= 1) then
            write (unit=error_unit, fmt='(A)') &
                '### error: file name expected'
            call mpi_abort(MPI_COMM_WORLD, 1)
        end if
        call get_command_argument(1, file_name)
    end if
    call mpi_bcast(file_name, file_name_lenght, MPI_CHARACTER, root, &
                   MPI_COMM_WORLD)
    sizes(1) = my_size
    subsizes(1) = 1
    starts(1) = my_rank
    call mpi_type_create_subarray(nr_dims, sizes, subsizes, starts, &
                                  MPI_ORDER_C, MPI_CHARACTER, &
                                  file_view)
    call mpi_type_commit(file_view)
    call mpi_file_open(MPI_COMM_WORLD, file_name, &
                       ior(MPI_MODE_WRONLY, MPI_MODE_CREATE), &
                       MPI_INFO_NULL, file_handle)
    disp = 0
    call mpi_file_set_view(file_handle, disp, MPI_CHARACTER, file_view, &
                           'native', MPI_INFO_NULL)
    buffer = achar(iachar('a') + my_rank)
    do i = 1, nr_chars
        call mpi_file_write_all(file_handle, &
                                   buffer, 1, MPI_CHARACTER, status)
    end do
    call mpi_file_close(file_handle)
    call mpi_type_free(file_view)
    call mpi_finalize()
end program views
