program time_funcs
    use :: math_func_mod, only : setup, functions
    use :: time_func_mod, only : time_func, time_func_unrolled, &
                                 result_record
    implicit none
    integer :: i
    type(result_record) :: result
    character(len=80) :: fmt_str = "(A10, A1, F12.6, A1, E20.6)"

    call setup()
    do i = 1, size(functions)
        print "('# starting ', A10)", functions(i)%name
        result = time_func(functions(i)%f)
        print fmt_str, functions(i)%name, ";", &
                       result%time, ";", result%result
    end do
    write (*, "('# unrolled')")
    do i = 1, size(functions)
        print "('# starting ', A10)", functions(i)%name
        result = time_func_unrolled(functions(i)%f)
        print fmt_str, functions(i)%name, ";", &
                       result%time, ";", result%result
    end do

end program time_funcs

