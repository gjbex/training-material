program select_test
    use :: iso_fortran_env, only : error_unit
    implicit none
    integer :: a, b
    character(len=40) :: buffer
    character(len=1) :: operator

    if (command_argument_count() /= 3) then
        write (unit=error_unit, fmt='(A)') &
                '# error: 3 arguments expected'
        stop 1
    end if

    call get_command_argument(1, buffer)
    read (buffer, '(I3)') a
    call get_command_argument(2, buffer)
    operator = trim(buffer)
    call get_command_argument(3, buffer)
    read (buffer, '(I3)') b

    select case (operator)
        case ('+')
            print "(I0, ' ', A, ' ', I0, ' = ', I0)", a, operator, b, a + b
        case ('*')
            print "(I0, ' ', A, ' ', I0, ' = ', I0)", a, operator, b, a * b
        case default
            write (unit=error_unit, fmt='(3A)')  &
                    '# error: unknown operand ''', operator, ''''
            stop 2
    end select
            
end program select_test
