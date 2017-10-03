program init_proc_vars
    implicit none
    integer, parameter :: nr_elems = 5, nr_arrays = 5
    integer, dimension(nr_elems) :: a
    integer :: i, nr_ones
    do i = 1, nr_arrays
        call init_array(a)
        nr_ones = count_one_wrong(a)
        print '(I5, I4, A, I1)', i, nr_ones, '/', size(a)
    end do

contains

    subroutine init_array(a)
        use, intrinsic :: iso_fortran_env, only : dp => REAL64
        implicit none
        integer, dimension(:), intent(inout) :: a
        integer :: i
        real(kind=dp) :: r
        
        do i = 1, size(a)
            call random_number(r)
            if (r < 0.5) then
                a(i) = 0
            else
                a(i) = 1
            end if
        end do
    end subroutine init_array

    function count_one_wrong(a) result(result)
        implicit none
        integer, dimension(:), intent(in) :: a
        integer :: result
        integer :: count = 0
        integer :: i
        do i = 1, size(a)
            if (a(i) > 0) count = count + 1
        end do
        result = count
    end function count_one_wrong

end program init_proc_vars
