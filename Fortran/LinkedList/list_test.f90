program list_test
    use linked_list_mod
    use, intrinsic :: iso_fortran_env, only : dp => REAL64
    implicit none
    type(list_type) :: list
    integer, parameter :: nr_vals = 10
    integer :: i, istat
    real(kind=dp), dimension(nr_vals) :: vals
    real(kind=dp) :: val
    
    vals = [ (sqrt(real(i - 1, kind=dp)), i=1, nr_vals) ]

    ! push to list
    do i = 1, size(vals)
        call list%push(vals(i))
        print "('pushed ', F10.4, ', length ', I0)", &
            vals(i), list%get_length()
    end do

    ! shift from list
    do while (.not. list%is_empty())
        call list%shift(val=val)
        print "('shifted ', F10.4, ', length ', I0)", &
            val, list%get_length()
    end do

    ! unshift to list
    do i = 1, size(vals)
        call list%unshift(vals(i))
        print "('unshifted ', F10.4, ', length ', I0)", &
            vals(i), list%get_length()
    end do

    ! pop from list
    do while (.not. list%is_empty())
        call list%pop(val=val)
        print "('popped ', F10.4, ', length ', I0)", &
            val, list%get_length()
    end do

    ! push to list
    do i = 1, size(vals)
        call list%push(vals(i))
        print "('pushed ', F10.4, ', length ', I0)", &
            vals(i), list%get_length()
    end do

    ! get vals
    do i = 1, list%get_length()
        call list%get(i, val)
        print "('got ', F10.4, ' from ', I0)", val, i
    end do

    ! insert vals
    do i = list%get_length(), 1, -1
        call list%insert(i, -1.0_dp)
    end do

    ! get vals
    do i = 1, list%get_length()
        call list%get(i, val)
        print "('got ', F10.4, ' from ', I0)", val, i
    end do

    ! remove vals
    do i = 1, list%get_length()/2
        call list%remove(i, val)
        print "('removed ', F10.4, ' from ', I0)", val, i
    end do

    ! get vals
    do i = 1, list%get_length()
        call list%get(i, val)
        print "('got ', F10.4, ' from ', I0)", val, i
    end do

    print '(A)', 'list:'
    call list%print_list()

    ! clear list
    call list%clear()
    print '(A)', 'list:'
    call list%print_list()

    ! check for error
    i = 3
    call list%get(i, val=val, stat=istat)
    if (istat /= 0) print "('get at ', I0, ' failed as intended')", i

end program list_test
