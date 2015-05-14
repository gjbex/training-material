program list_test
    use linked_list_mod
    use, intrinsic :: iso_fortran_env, only : dp => REAL64
    implicit none
    type(list_type) :: list
    integer, parameter :: nr_values = 10
    integer :: i
    real(kind=dp), dimension(nr_values) :: values
    real(kind=dp) :: value, value1
    
    values = [ (sqrt(real(i - 1, kind=dp)), i=1, nr_values) ]

    ! push to list
    do i = 1, size(values)
        call list%push(values(i))
        print "('pushed ', F10.4, ', length ', I0)", &
            values(i), list%get_length()
    end do

    ! shift from list
    do while (.not. list%is_empty())
        call list%shift(value=value)
        print "('shifted ', F10.4, ', length ', I0)", &
            value, list%get_length()
    end do

    ! unshift to list
    do i = 1, size(values)
        call list%unshift(values(i))
        print "('unshifted ', F10.4, ', length ', I0)", &
            values(i), list%get_length()
    end do

    ! pop from list
    do while (.not. list%is_empty())
        call list%pop(value=value)
        print "('popped ', F10.4, ', length ', I0)", &
            value, list%get_length()
    end do

    ! push to list
    do i = 1, size(values)
        call list%push(values(i))
        print "('pushed ', F10.4, ', length ', I0)", &
            values(i), list%get_length()
    end do

    ! get values
    do i = 1, list%get_length()
        call list%get(i, value)
        print "('got ', F10.4, ' from ', I0)", value, i
    end do

    ! insert values
    do i = list%get_length(), 1, -1
        call list%insert(i, -1.0_dp)
    end do

    ! get values
    do i = 1, list%get_length()
        call list%get(i, value)
        print "('got ', F10.4, ' from ', I0)", value, i
    end do

    ! remove values
    do i = 1, list%get_length()/2
        call list%remove(i, value)
        print "('removed ', F10.4, ' from ', I0)", value, i
    end do

    ! get values
    do i = 1, list%get_length()
        call list%get(i, value)
        print "('got ', F10.4, ' from ', I0)", value, i
    end do

    print '(A)', 'list:'
    call list%print_list()

    ! clear list
    call list%clear()
    print '(A)', 'list:'
    call list%print_list()

end program list_test
