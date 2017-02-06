program diffusion
use iso_fortran_env, only : REAL64
use cl_params
use system_class
implicit none

    integer :: next
    integer, parameter :: file_unit = 9
    type(params_type) :: params
    type(system_type) :: system
    integer :: time, next_time, istat
    real(kind=REAL64) :: r

    call init_cl(params)
    call parse_cl(params, next)
    call dump_cl(output_unit, '# ', params)

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
    stop

end program diffusion

