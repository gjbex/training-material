module cl_params
use iso_fortran_env, only : REAL64, error_unit
implicit none

    type :: params_type
        integer :: n
        real(kind=REAL64) :: init_temp
        integer :: nr_spots
        real(kind=REAL64) :: spot_size
        real(kind=REAL64) :: max_spot_temp
        integer :: max_time
        real(kind=REAL64) :: diff_coeff
        integer :: avg_delta
        logical :: verbose
        character(len=1024) :: output_file
    end type params_type

contains

    subroutine shift_cl(last, argv)
        integer, intent(inout) :: last
        character(len=*), intent(inout) :: argv
        if (last < command_argument_count()) then
            last = last + 1
            call get_command_argument(last, argv)
        else
            write (error_unit, '(A)') &
                '### error: option ''' // trim(argv) // ''' expects a value'
            stop
        end if
        return
    end subroutine shift_cl
    
    subroutine trim_quotes_cl(str)
        character(len=*), intent(inout) :: str
        integer :: i
        do i = 2, len_trim(str)
        end do
    end subroutine trim_quotes_cl

    subroutine init_cl(params)
        type(params_type), intent(out) :: params
        params % n = 10
        params % init_temp = 0.0D00
        params % nr_spots = 1
        params % spot_size = 3.0D00
        params % max_spot_temp = 0.5D00
        params % max_time = 10
        params % diff_coeff = 1.0D00
        params % avg_delta = 3
        params % verbose = .false.
        params % output_file = ''
    end subroutine init_cl

    subroutine parse_cl(params, next)
        type(params_type), intent(inout) :: params
        integer, intent(out), optional :: next
        integer :: last, status
        character(len=1024) :: argv
        last = 1
        status = 0
        do
            if (last <= command_argument_count()) then
                call get_command_argument(last, argv)
                select case (argv)
                    case ('-n')
                        call shift_cl(last, argv)
                        read (argv, fmt=*, iostat=status) params % n
                        if (status /= 0) then
                            write (error_unit, '(A)') &
                                '### error: invalid value for option ' // &
                                '''-n'' ' // &
                                'of type integer'
                                stop
                        end if
                    case ('-init_temp')
                        call shift_cl(last, argv)
                        read (argv, fmt=*, iostat=status) params % init_temp
                        if (status /= 0) then
                            write (error_unit, '(A)') &
                                '### error: invalid value for option ' // &
                                '''-init_temp'' ' // &
                                'of type real(kind=REAL64)'
                                stop
                        end if
                    case ('-nr_spots')
                        call shift_cl(last, argv)
                        read (argv, fmt=*, iostat=status) params % nr_spots
                        if (status /= 0) then
                            write (error_unit, '(A)') &
                                '### error: invalid value for option ' // &
                                '''-nr_spots'' ' // &
                                'of type integer'
                                stop
                        end if
                    case ('-spot_size')
                        call shift_cl(last, argv)
                        read (argv, fmt=*, iostat=status) params % spot_size
                        if (status /= 0) then
                            write (error_unit, '(A)') &
                                '### error: invalid value for option ' // &
                                '''-spot_size'' ' // &
                                'of type real(kind=REAL64)'
                                stop
                        end if
                    case ('-max_spot_temp')
                        call shift_cl(last, argv)
                        read (argv, fmt=*, iostat=status) params % max_spot_temp
                        if (status /= 0) then
                            write (error_unit, '(A)') &
                                '### error: invalid value for option ' // &
                                '''-max_spot_temp'' ' // &
                                'of type real(kind=REAL64)'
                                stop
                        end if
                    case ('-max_time')
                        call shift_cl(last, argv)
                        read (argv, fmt=*, iostat=status) params % max_time
                        if (status /= 0) then
                            write (error_unit, '(A)') &
                                '### error: invalid value for option ' // &
                                '''-max_time'' ' // &
                                'of type integer'
                                stop
                        end if
                    case ('-diff_coeff')
                        call shift_cl(last, argv)
                        read (argv, fmt=*, iostat=status) params % diff_coeff
                        if (status /= 0) then
                            write (error_unit, '(A)') &
                                '### error: invalid value for option ' // &
                                '''-diff_coeff'' ' // &
                                'of type real(kind=REAL64)'
                                stop
                        end if
                    case ('-avg_delta')
                        call shift_cl(last, argv)
                        read (argv, fmt=*, iostat=status) params % avg_delta
                        if (status /= 0) then
                            write (error_unit, '(A)') &
                                '### error: invalid value for option ' // &
                                '''-avg_delta'' ' // &
                                'of type integer'
                                stop
                        end if
                    case ('-verbose')
                        params % verbose = .true.
                    case ('-output_file')
                        call shift_cl(last, argv)
                        params % output_file = trim(argv)
                        if (status /= 0) then
                            write (error_unit, '(A)') &
                                '### error: invalid value for option ' // &
                                '''-output_file'' ' // &
                                'of type character(len=1024)'
                                stop
                        end if
                    case default
                        exit
                end select
            else
                exit
            end if
            last = last + 1
        end do
        if (present(next)) then
            next = last
        end if
        return
    end subroutine parse_cl

    subroutine parse_file_cl(params, file_name)
        type(params_type), intent(inout) :: params
        character(len=1024), intent(in) :: file_name
        integer :: status, file_unit = 8
        character(len=1024) :: line_str, arg_name, sep, argv
        status = 0
        open(unit=file_unit, file=file_name, action='READ', iostat=status)
        if (status /= 0) then
            write (error_unit, '(A)') &
                '### error: can not open file ' // file_name
            stop
        end if
        do
            read(file_unit, '(A)', iostat=status) line_str
            if (status /= 0) exit
            if (len_trim(line_str) == 0) cycle
            if (index(trim(line_str), '#') == 1) cycle
            read (line_str, *, iostat=status) arg_name, sep, argv
            if (status == 0) then
                if (sep /= '=') then
                    write (error_unit, '(A)') &
                        '### error, invalid line format: ' // line_str
                    stop
                end if
                select case (arg_name)
                    case ('n')
                        read (argv, fmt=*, iostat=status) params % n
                        if (status /= 0) then
                            write (error_unit, '(A)') &
                                '### error: invalid value for option ' // &
                                '''n'' ' // &
                                'of type integer'
                                stop
                        end if
                    case ('init_temp')
                        read (argv, fmt=*, iostat=status) params % init_temp
                        if (status /= 0) then
                            write (error_unit, '(A)') &
                                '### error: invalid value for option ' // &
                                '''init_temp'' ' // &
                                'of type real(kind=REAL64)'
                                stop
                        end if
                    case ('nr_spots')
                        read (argv, fmt=*, iostat=status) params % nr_spots
                        if (status /= 0) then
                            write (error_unit, '(A)') &
                                '### error: invalid value for option ' // &
                                '''nr_spots'' ' // &
                                'of type integer'
                                stop
                        end if
                    case ('spot_size')
                        read (argv, fmt=*, iostat=status) params % spot_size
                        if (status /= 0) then
                            write (error_unit, '(A)') &
                                '### error: invalid value for option ' // &
                                '''spot_size'' ' // &
                                'of type real(kind=REAL64)'
                                stop
                        end if
                    case ('max_spot_temp')
                        read (argv, fmt=*, iostat=status) params % max_spot_temp
                        if (status /= 0) then
                            write (error_unit, '(A)') &
                                '### error: invalid value for option ' // &
                                '''max_spot_temp'' ' // &
                                'of type real(kind=REAL64)'
                                stop
                        end if
                    case ('max_time')
                        read (argv, fmt=*, iostat=status) params % max_time
                        if (status /= 0) then
                            write (error_unit, '(A)') &
                                '### error: invalid value for option ' // &
                                '''max_time'' ' // &
                                'of type integer'
                                stop
                        end if
                    case ('diff_coeff')
                        read (argv, fmt=*, iostat=status) params % diff_coeff
                        if (status /= 0) then
                            write (error_unit, '(A)') &
                                '### error: invalid value for option ' // &
                                '''diff_coeff'' ' // &
                                'of type real(kind=REAL64)'
                                stop
                        end if
                    case ('avg_delta')
                        read (argv, fmt=*, iostat=status) params % avg_delta
                        if (status /= 0) then
                            write (error_unit, '(A)') &
                                '### error: invalid value for option ' // &
                                '''avg_delta'' ' // &
                                'of type integer'
                                stop
                        end if
                    case ('verbose')
                        read (argv, fmt=*, iostat=status) params % verbose
                        if (status /= 0) then
                            write (error_unit, '(A)') &
                                '### error: invalid value for option ' // &
                                '''verbose'' ' // &
                                'of type logical'
                                stop
                        end if
                    case ('output_file')
                        params % output_file = trim(argv)
                        if (status /= 0) then
                            write (error_unit, '(A)') &
                                '### error: invalid value for option ' // &
                                '''output_file'' ' // &
                                'of type character(len=1024)'
                                stop
                        end if
                    case default
                        write (error_unit, '(A)') &
                            '### warning, unknown parameter ''' // &
                             arg_name // ''' in line: ' // line_str
                end select
            else
                write (error_unit, '(A)') &
                    '### error, invalid line format: ' // line_str
                stop
            end if
        end do
        return
    end subroutine parse_file_cl

    subroutine dump_cl(unit_nr, prefix, params)
        integer, intent(in) :: unit_nr
        character(len=*), intent(in) :: prefix
        type(params_type), intent(in) :: params
        write (unit_nr, '(A, I20)') &
            prefix // &
            'n = ', params % n
        write (unit_nr, '(A, F24.15)') &
            prefix // &
            'init_temp = ', params % init_temp
        write (unit_nr, '(A, I20)') &
            prefix // &
            'nr_spots = ', params % nr_spots
        write (unit_nr, '(A, F24.15)') &
            prefix // &
            'spot_size = ', params % spot_size
        write (unit_nr, '(A, F24.15)') &
            prefix // &
            'max_spot_temp = ', params % max_spot_temp
        write (unit_nr, '(A, I20)') &
            prefix // &
            'max_time = ', params % max_time
        write (unit_nr, '(A, F24.15)') &
            prefix // &
            'diff_coeff = ', params % diff_coeff
        write (unit_nr, '(A, I20)') &
            prefix // &
            'avg_delta = ', params % avg_delta
        write (unit_nr, '(A, L)') &
            prefix // &
            'verbose = ', params % verbose
        write (unit_nr, '(A)') &
            prefix // &
            'output_file = ''' // trim(params % output_file) // ''''
        return
    end subroutine dump_cl

end module cl_params
