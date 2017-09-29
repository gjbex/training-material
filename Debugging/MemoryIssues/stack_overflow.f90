program stack_overflow
    use, intrinsic :: iso_fortran_env, only : i64 => INT64
    implicit none
    integer(kind=i64) :: n
    character(len=80) :: buffer

    if (command_argument_count() > 0) then
        call get_command_argument(1, buffer)
        read (buffer, '(I20)') n
    else
        n = 5_i64
    end if
    print '(I5, A, I20)', n, ' = ', fib(n)

contains

    recursive function fib(n) result(r)
        use, intrinsic :: iso_fortran_env, only : i64 => INT64
        implicit none
        integer(kind=i64), intent(in) :: n
        integer(kind=i64) :: r
        r = fib(n-1) + fib(n-2)
    end function fib

end program stack_overflow
