program allocation_error
    use, intrinsic :: iso_fortran_env, only : error_unit
    implicit none
    integer, parameter :: allocation_err = 1
    real, dimension(:), allocatable :: data
    integer :: n, istat
    character(len=80) :: buffer

    if (command_argument_count() == 1) then
        call get_command_argument(1, buffer)
        read (buffer, fmt='(I10)') n
    else
        n = 10
    end if 
    allocate(data(n), stat=istat)
    if (istat /= 0) then
        write (unit=error_unit, fmt='(A, I3, A, I10)') &
            '### error in ' // trim(__FILE__) // ',', __LINE__, &
            ': can not allocate array of size ', n
        stop allocation_err
    end if
    call init_array(data)
    print '(A, E15.5)', 'result = ', compute_something(data)

    contains

        subroutine init_array(data)
            implicit none
            real, dimension(:), intent(inout) :: data
            call random_number(data)
        end subroutine init_array

        real function compute_something(data)
            implicit none
            real, dimension(:), intent(inout) :: data
            real :: total
            integer :: i
            total = 0.0
            do i = 1, size(data)
                total = total + data(i)
            end do
            compute_something = total
        end function compute_something

end program allocation_error
