program diffusion

    use iso_fortran_env, only : REAL64, error_unit, output_unit
    use mpi_f08
    use cl_params, only : init_cl, parse_cl
    use system_class
    implicit none

    integer :: next
    integer, parameter :: file_unit = 9
    type(params_type) :: params
    type(system_type) :: system
    integer :: time, next_time, istat
    integer :: rank, size
    integer, parameter :: root = 0, ndims = 2
    integer, dimension(ndims) :: dims = 0
    logical, dimension(ndims) :: periods = .false.
    logical, parameter :: reorder = .true.
    type(MPI_Comm) :: cart_comm
    integer :: upper, right, lower, left
    type(MPI_Datatype) :: row_type, col_type
    real(kind=REAL64) :: r

    call MPI_Init()
    call MPI_Comm_rank(MPI_COMM_WORLD, rank)
    call MPI_Comm_size(MPI_COMM_WORLD, size)

! rearrange processes in carthesian communicator and determine
! neighbour ranks
    call MPI_Dims_create(size, ndims, dims)
    if (rank == root) then
        print '(A, I3, I3)', '# dimensions: ', dims(1), dims(2)
    end if
    call MPI_Cart_create(MPI_COMM_WORLD, ndims, dims, periods, &
                         reorder, cart_comm)
    call MPI_Comm_rank(cart_comm, rank)
    call MPI_Cart_shift(cart_comm, 0, 1, upper, lower)
    call MPI_Cart_shift(cart_comm, 1, 1, left, right)
    
     print '(A, I3, A, 4I3)', '# neighbours for ', rank, ': ', &
        upper, right, lower, left
    call MPI_Barrier(cart_comm)

! This is a shortcut, assuming all processes can access command line
! argument TODO: fix by making root handle arguments, and broadcast
    call init_cl(params)
    call parse_cl(params, next)
    if (rank == root) then
        call dump_cl(output_unit, '# ', params)
    end if

    call create_types(params, row_type, col_type)

    call system%init(params)
    call system%apply_laser(params)
    if (params%verbose) call system%show(time=time)
    print '(I10, F15.4)', time, system%avg_temp()
    call random_number(r)
    next_time = 2 + int(r*params%avg_delta)
    do time = 1, params%max_time
        if (time == next_time) then
            if (params%verbose) write (output_unit, '(A)') 'zap!!'
            call system%apply_laser(params)
            call random_number(r)
            next_time = time + 1 + int(r*params%avg_delta)
        end if
        call system%step()
        if (params%verbose) call system%show(time=time)
        print '(I10,F15.4)', time, system%avg_temp()
    end do
    if (len(trim(params%output_file)) > 0) then
        open(unit=file_unit, file=trim(params%output_file), iostat=istat, &
             action='WRITE', status='REPLACE')
        if (istat /= 0) then
            write(error_unit, '(2A)') "### error: can not open file ", &
                trim(params%output_file)
            stop
        end if
        call system%show(unit=file_unit)
        close(unit=file_unit)
    end if
    call system%delete()

    call MPI_Finalize()

contains

    subroutine create_types(params, row_type, col_type)
        implicit none
        type(params_type), intent(in) :: params
        type(MPI_Datatype), intent(inout) :: row_type, col_type
        call MPI_Type_vector(params%n, 1, params%n - 2, &
                             MPI_DOUBLE_PRECISION, row_type)
        call MPI_Type_commit(row_type)
        call MPI_Type_contiguous(params%n - 1, MPI_DOUBLE_PRECISION, &
                                 col_type)
        call MPI_Type_commit(col_type)
    end subroutine create_types

    subroutine exchange_halos(comm, row_type, col_type, &
                              upper, right, lower, left, system)
        implicit none
        type(MPI_Comm), intent(in) :: comm
        type(MPI_Datatype), intent(in) :: row_type, col_type
        integer, intent(in) :: upper, right, lower, left
        type(system_type), intent(inout) :: system
        real(kind=REAL64), dimension(system%n()) :: buffer
    end subroutine exchange_halos

end program diffusion

