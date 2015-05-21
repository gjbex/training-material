program static_array_in_function_test
    implicit none
    integer, parameter :: n = 100

    print '(F10.5)', compute_normal_avg(n)

contains

    function compute_normal_avg(n) result(average)
        use, intrinsic :: iso_fortran_env, only : REAL32
        implicit none
        integer, intent(in) :: n
        real(kind=REAL32) :: average
        real(kind=REAL32), dimension(n) :: v

        call random_number(v)
        average = sum(v)/n

    end function compute_normal_avg

end program static_array_in_function_test
