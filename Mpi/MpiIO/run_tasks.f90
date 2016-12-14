program tasks
    use :: iso_fortran_env, only : output_unit, error_unit
    use :: mpi_f08
    use :: tasks_mod, only : task_type, create_task_type, free_task_type
    implicit none
    integer, parameter :: file_name_length = 1024, root = 0
    integer :: my_size, my_rank, count
    integer(kind=MPI_OFFSET_KIND) :: disp = 0
    character(len=file_name_length) :: file_name, buffer
    type(MPI_Datatype) :: task_mpi_type
    type(task_type) :: task
    type(MPI_File) :: file_handle
    type(MPI_Status) :: status

    call mpi_init()
    call mpi_comm_size(MPI_COMM_WORLD, my_size)
    call mpi_comm_rank(MPI_COMM_WORLD, my_rank)
    
    ! root deals with command line arguments and broadcasts
    if (my_rank == root) then
        if (command_argument_count() == 0) then
            write(unit=error_unit, fmt='(A)') &
                '### error: no file name specified'
            call mpi_abort(MPI_COMM_WORLD, 1)
        end if
        call get_command_argument(1, file_name)
    end if
    call mpi_bcast(file_name, file_name_length, MPI_CHARACTER, root, &
                   MPI_COMM_WORLD)
    call create_task_type(task_mpi_type)
    call mpi_file_open(MPI_COMM_WORLD, file_name, MPI_MODE_RDONLY, &
                       MPI_INFO_NULL, file_handle)
    call mpi_file_set_view(file_handle, disp, task_mpi_type, &
                           task_mpi_type, 'native', MPI_INFO_NULL)
    do while (.true.)
        call mpi_file_read_shared(file_handle, task, 1, task_mpi_type, &
                                  status)
        call mpi_get_count(status, task_mpi_type, count)
        if (count /= 1) exit
        call sleep(1 + mod(task%param, 3))
        write(unit=output_unit, fmt="(A, I2, ', ', A, I10, I10)") &
            'rank ', my_rank, task%name, task%param, count
    end do
    
    call mpi_file_close(file_handle)

    call free_task_type(task_mpi_type)
    call mpi_finalize()
end program tasks
