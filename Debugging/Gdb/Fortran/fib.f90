program fibonacci
    use, intrinsic :: iso_fortran_env, only : error_unit
    implicit none
    character(len=80) :: buffer
    integer :: n
    
      if (command_argument_count() > 0) then
          call get_command_argument(1, buffer)
          read (buffer, fmt='(I10)') n
      else
          write (unit=error_unit, fmt='(A)') &
              '### error: no argument to command'
          stop 1
      end if
      print '(I20)', fib(n)
    
    contains

        recursive function fib(n) result(f)
            implicit none
            integer, intent(in) :: n
            integer :: f
            f = fib(n - 1) + fib(n - 2)
        end function fib

end program fibonacci
