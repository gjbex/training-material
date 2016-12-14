module tasks_mod
    use :: mpi_f08
    implicit none

    integer, parameter :: name_length = 12

    type :: task_type
        sequence
        integer :: param
        character(len=12) :: name
    end type task_type

contains

    subroutine create_task_type(task_mpi_type)
        type(MPI_Datatype), intent(out) :: task_mpi_type
        integer, parameter :: nr_blocks = 2
        integer, dimension(nr_blocks) :: block_lengths
        integer(kind=MPI_ADDRESS_KIND), dimension(nr_blocks) :: block_disps
        type(MPI_Datatype), dimension(nr_blocks) :: block_types
        type(task_type) :: task
        integer(kind=MPI_ADDRESS_KIND) :: name_addr, param_addr

        block_lengths(1) = 1
        block_disps(1) = 0
        block_types(1) = MPI_INTEGER
        call mpi_get_address(task%name, name_addr)
        call mpi_get_address(task%param, param_addr)
        block_lengths(2) = name_length
        block_disps(2) = mpi_aint_diff(name_addr, param_addr)
        block_types(2) = MPI_CHARACTER
        call mpi_type_create_struct(nr_blocks, block_lengths, &
                                    block_disps, block_types, &
                                    task_mpi_type)
        call mpi_type_commit(task_mpi_type)
    end subroutine create_task_type

    subroutine free_task_type(task_mpi_type)
        type(MPI_Datatype), intent(inout) :: task_mpi_type
        call mpi_type_free(task_mpi_type)
    end subroutine free_task_type
    
end module tasks_mod
