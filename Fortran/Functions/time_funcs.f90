program time_funcs
    use math_func_mod
    use time_func_mod
    implicit none
    integer :: i
    type(result_record) :: result

    call setup()
    do i = 1, size(functions)
        print "('# starting ', A10)", functions(i)%name
        result = time_func(functions(i)%f)
        print "(A10, A1, F12.6, A1, E20.6)", functions(i)%name, ";", &
                                             result%time, ";",       &
                                             result%result
    end do
    write (*, "('# unrolled')")
    do i = 1, size(functions)
        print "('# starting ', A10)", functions(i)%name
        result = time_func_unrolled(functions(i)%f)
        print "(A10, A1, F12.6, A1, E20.6)", functions(i)%name, ";", &
                                             result%time, ";",       &
                                             result%result
    end do

end program time_funcs

