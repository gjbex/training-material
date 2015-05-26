program xw_test
    use, intrinsic :: iso_fortran_env, only : dp => REAL64
    use :: gauss_mod
    implicit none
    type(gen_gauss_type) :: gen_gauss_quad
    integer, parameter :: default_n = 10
    integer :: n
    character(len=20) :: buffer

    if (command_argument_count() >= 1) then
        call get_command_argument(1, buffer)
        read (buffer, '(I10)') n
    else
        n = default_n
    end if

    call gen_gauss_quad%init_gen_gauss(n, precision=1.0e-15_dp)
    print '(2A20)', 'abscis', 'weight'
    call gen_gauss_quad%print_params()

end program xw_test
