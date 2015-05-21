program failed_allocate_test
    use, intrinsic :: iso_fortran_env, only : INT32, INT64
    implicit none
    integer(kind=INT64), parameter :: init_size = 5000, size_step = 5000
    integer(kind=INT32), dimension(:, :), allocatable :: A
    integer :: istat
    integer(kind=INT64) :: size
    real :: total_size

    size = init_size
    do while(.true.)
        allocate(A(size, size), stat=istat)
        total_size = 4.0*size**2/(1024**2)
        if (.not. allocated(A)) &
            print '(A)', 'allocated returns .false.'
        if (istat /= 0) then
            print '(A, F10.2, A)', 'array of size ', total_size, &
                    ' MB not allocated'
            exit
        else
            print '(A, F10.2, A)', 'array of size ', total_size, &
                    ' MB allocated'
        end if
        deallocate(A)
        size = size + size_step
    end do

end program failed_allocate_test
