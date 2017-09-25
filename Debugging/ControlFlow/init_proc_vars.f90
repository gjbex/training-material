program init_proc_vars
    implicit none
    integer, parameter :: nr_elems = 5, nr_arrays = 5
    integer, dimension(nr_elems) :: a
    integer, dimension(nr_arrays) :: right, wrong
    integer :: i
    do i = 1, nr_arrays
        call init_array(a)
        wrong(i) = count_one_wrong(a)
        right(i) = count_one_right(a)
    end do
    print '(A)', 'wrong:'
    do i = 1, nr_arrays
        print '(I5, I10)', i, wrong(i)
    end do
    print '(A)', 'right:'
    do i = 1, nr_arrays
        print '(I5, I10)', i, right(i)
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

    function count_one_wrong(a) result(count)
        implicit none
        integer, dimension(:), intent(in) :: a
        integer :: count
        integer :: c = 0
        integer :: i
        do i = 1, size(a)
            if (a(i) > 0) c = c + 1
        end do
        count = c
    end function count_one_wrong

    function count_one_right(a) result(count)
        implicit none
        integer, dimension(:), intent(in) :: a
        integer :: count
        integer :: i
        count = 0
        do i = 1, size(a)
            if (a(i) > 0) count = count + 1
        end do
    end function count_one_right

end program init_proc_vars
