program env_test
    use, intrinsic :: iso_fortran_env, only : error_unit
    implicit none
    integer, parameter :: env_not_defined_err = 1, &
                          env_too_long_err    = 2
    character(len=50), parameter :: var_name = 'MY_ENV_VAR', &
                                    home_var_name = 'HOME'
    character(len=100) :: value
    character(len=3) :: short_value
    integer :: status, length

    call get_environment_variable(home_var_name, value, length, status)
    print '(2A)', 'home directory: ', trim(value)

    call get_environment_variable(var_name, short_value, length, status)
    print '(3A)', trim(var_name), ' = ', trim(short_value)
    print '(TR4, A, I0)', 'length read: ', length
    print '(TR4, A, I0)', 'status: ', status
    if (status > 0) then
        write (unit=error_unit, fmt='(3A)') &
                '# error: ', trim(var_name), ' not defined'
        stop env_not_defined_err
    else if (status < 0) then
        write (unit=error_unit, fmt='(3A)') &
                '# error: ', trim(var_name), ' longer than expected'
        stop env_too_long_err
    end if

end program env_test
