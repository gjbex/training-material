program tasks
    use :: iso_fortran_env, only : error_unit
    use :: mpi_f08
    use :: tasks_mod, only : task_type, create_task_type, free_task_type
    implicit none
    integer, parameter :: file_name_length = 1024, root = 0
    integer :: my_size, my_rank, nr_tasks, task_nr
    integer(kind=MPI_OFFSET_KIND) :: disp = 0
    character(len=file_name_length) :: file_name, buffer
    real :: r
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
        if (command_argument_count() > 1) then
            call get_command_argument(2, buffer)
            read (buffer, '(I10)') nr_tasks
        else
            nr_tasks = 100
        end if
    end if
    call mpi_bcast(file_name, file_name_length, MPI_CHARACTER, root, &
                   MPI_COMM_WORLD)
    call mpi_bcast(nr_tasks, 1, MPI_INTEGER, root, MPI_COMM_WORLD)
    call create_task_type(task_mpi_type)
    call mpi_file_open(MPI_COMM_WORLD, file_name, &
                       ior(MPI_MODE_WRONLY, MPI_MODE_CREATE), &
                       MPI_INFO_NULL, file_handle)
    call mpi_file_set_view(file_handle, disp, task_mpi_type, &
                           task_mpi_type, 'native', MPI_INFO_NULL)
    do task_nr = 1, nr_tasks
        write (task%name, '(A5, I7)') 'task ', task_nr
        call random_number(r)
        task%param = int(1000*r)
        print "(I3, ':', A12)", task%param, task%name
        call mpi_file_write_all(file_handle, task, 1, task_mpi_type, status)
    end do
    
    call mpi_file_close(file_handle)

    call free_task_type(task_mpi_type)
    call mpi_finalize()
end program tasks
