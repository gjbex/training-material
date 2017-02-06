program diffusion

    use iso_fortran_env, only : REAL64
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
    integer, parameter :: root = 0
    real(kind=REAL64) :: r

    call MPI_Init()
    call MPI_Comm_rank(MPI_COMM_WORLD, rank)
    call MPI_Comm_size(MPI_COMM_WORLD, size)

    if (rank == root) then
        call init_cl(params)
        call parse_cl(params, next)
        call dump_cl(output_unit, '# ', params)
    end if

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
            print *, "### error: can not open file " // trim(params%output_file)
            stop
        end if
        call system%show(unit=file_unit)
        close(unit=file_unit)
    end if
    call system%delete()

    call MPI_Finalize()

end program diffusion

