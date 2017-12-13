program udt_intent_out
implicit none
    integer, parameter :: nr_elems = 100
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
    call initialize(r, nr_elems + 16)
    print '(A8, F5.1)', 'after: ', r%x(nr_elems)
    print '(A8, F5.1)', 'after: ', r%x(nr_elems + 15)
    print '(A8, F5.1)', 'after: ', r%y(15)
    print '(A8, F5.1)', 'after: ', r%y(nr_elems)

contains

    subroutine initialize(r, n)
        implicit none
        type(record), intent(out) :: r
        integer :: n
        allocate(r%x(n))
        r%x = 5.0
    end subroutine initialize

end program udt_intent_out
