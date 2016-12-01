program explicit_offsets
    use :: iso_fortran_env, only : error_unit
    use :: mpi_f08
    implicit none
    integer, parameter :: file_name_lenght = 1024, nr_chars = 5
    integer :: my_rank, my_size, root, i
    character(len=file_name_lenght) :: file_name
    type(MPI_File) :: file_handle
    type(MPI_Status) :: status
    integer(kind=MPI_OFFSET_KIND) :: offset
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
    call mpi_file_open(MPI_COMM_WORLD, file_name, &
                       ior(MPI_MODE_WRONLY, MPI_MODE_CREATE), &
                       MPI_INFO_NULL, file_handle)
    offset = my_rank
    buffer = achar(iachar('a') + my_rank)
    do i = 1, nr_chars
        call mpi_file_write_at(file_handle, offset, &
                                buffer, 1, MPI_CHARACTER, status)
        offset = offset + my_size
    end do
    call mpi_file_close(file_handle)
    call mpi_finalize()

end program explicit_offsets
