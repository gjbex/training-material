program udt_intent_out
implicit none
    integer, parameter :: nr_elems = 100, incr = 16
    type record
        real, dimension(:), allocatable :: x
        real, dimension(:), allocatable :: y
    end type record
    type(record) :: r

    allocate(r%x(nr_elems))
    r%x = 2.0
    allocate(r%y(nr_elems))
    r%y = 3.0
    print '(A8, 3F5.1)', 'before: ', r%x(nr_elems), r%y(15), r%y(nr_elems)
    call initialize_inout(r, nr_elems + incr)
    print '(A8, 3F5.1)', 'after: ', r%x(nr_elems), r%y(incr), r%y(nr_elems)
    call initialize_out(r, nr_elems + 2*incr)
    print '(A8, 2F5.1)', 'after: ', r%x(nr_elems), r%x(nr_elems + 2*incr)
    print '(A8, F5.1)', 'after: ', r%y(2*incr)
    print '(A8, F5.1)', 'after: ', r%y(nr_elems)

contains

    subroutine initialize_out(r, n)
        implicit none
        type(record), intent(out) :: r
        integer :: n
        allocate(r%x(n))
        r%x = 5.0
    end subroutine initialize_out

    subroutine initialize_inout(r, n)
        implicit none
        type(record), intent(inout) :: r
        integer :: n
        if (.not. allocated(r%x)) then
            allocate(r%x(n))
        else
            print '(A)', 'x already allocated'
        end if
        r%x = 5.0
    end subroutine initialize_inout

end program udt_intent_out
