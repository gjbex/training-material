program select_test
implicit none
integer :: a, b
character(len=40) :: buffer
character(len=1) :: operator

if (command_argument_count() /= 3) then
    print *, '# error: 3 arguments expected'
    stop
end if

call get_command_argument(1, buffer)
read (buffer, '(I3)') a
call get_command_argument(2, buffer)
operator = trim(buffer)
call get_command_argument(3, buffer)
read (buffer, '(I3)') b

select case (operator)
    case ('+')
        print "(I3, A2, I3, ' = ', I6)", a, operator, b, a + b
    case ('*')
        print "(I3, A2, I3, ' = ', I6)", a, operator, b, a * b
    case default
        print "('# error: unknown operand ''', A, '''')", operator
end select
        
end program select_test
