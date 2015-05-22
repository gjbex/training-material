program xw_test
    use, intrinsic :: iso_fortran_env, only : dp => REAL64
    use :: gen_gauss_mod
    implicit none
    type(gen_gauss_type) :: gen_gauss_quad
    integer, parameter :: n = 100
    call gen_gauss_quad%init(n, precision=1.0e-15_dp)
    print '(2A20)', 'abscis', 'weight'
    call gen_gauss_quad%print_params()

end program xw_test
