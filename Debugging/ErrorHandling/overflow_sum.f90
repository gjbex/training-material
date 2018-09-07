program overflow_sum
    use, intrinsic :: ieee_arithmetic, only : ieee_is_normal
    use, intrinsic :: iso_fortran_env, only : error_unit
    implicit none
    integer :: n
    character(len=80) :: buffer
    real :: result

    n = 10
    if (command_argument_count() > 0) then
        call get_command_argument(1, buffer)
        read (buffer, '(I10)') n
    end if
    result = compute_sum(n)
    if (.not. ieee_is_normal(result)) then
        write (unit=error_unit, fmt='(A)') 'non-normal number detected'
    end if
    print '(A, E12.5)', 'result = ', result

    contains

        real function compute_sum(n)
            implicit none
            integer, intent(in) :: n
            integer :: i
            compute_sum = 0.0
            do i = 1, n
                compute_sum = compute_sum + 10.0**i
            end do
        end function compute_sum

end program overflow_sum
