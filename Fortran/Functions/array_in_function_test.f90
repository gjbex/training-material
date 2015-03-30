program static_array_in_function_test
    use, intrinsic :: iso_fortran_env
    implicit none
    integer, parameter :: n = 100
    real(kind=real32) :: result

    result = compute_normal_avg(n)
    print *, result

contains

    function compute_normal_avg(n) result(average)
        implicit none
        integer, intent(in) :: n
        real(kind=REAL32) :: average
        real(kind=REAL32), dimension(n) :: v
        real(kind=REAL32) :: random
        integer :: i

        do i = 1, n
            call random_number(random)
            v(i) = random
        end do

        average = sum(v)/n

    end function compute_normal_avg

end program static_array_in_function_test
