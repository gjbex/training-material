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

    ! append to list
    do i = 1, size(values)
        call list%append(values(i))
        print "('appended ', F10.4, ', length ', I0)", &
            values(i), list%get_length()
    end do

    ! shift from list
    do while (.not. list%is_empty())
        value = list%shift()
        print "('shifted ', F10.4, ', length ', I0)", &
            value, list%get_length()
    end do

    ! prepend to list
    do i = 1, size(values)
        call list%prepend(values(i))
        print "('prepended ', F10.4, ', length ', I0)", &
            values(i), list%get_length()
    end do

    ! pop from list
    do while (.not. list%is_empty())
        value = list%pop()
        print "('popped ', F10.4, ', length ', I0)", &
            value, list%get_length()
    end do

    ! append to list
    do i = 1, size(values)
        call list%append(values(i))
        print "('appended ', F10.4, ', length ', I0)", &
            values(i), list%get_length()
    end do

    ! get values
    do i = 1, list%get_length()
        print "('got ', F10.4, ' from ', I0)", list%get(i), i
    end do

    ! insert values
    do i = list%get_length(), 1, -1
        call list%insert(i, -1.0_dp)
    end do

    ! get values
    do i = 1, list%get_length()
        print "('got ', F10.4, ' from ', I0)", list%get(i), i
    end do

    ! remove values
    do i = 1, list%get_length()/2
        value = list%remove(i)
        print "('removed ', F10.4, ' from ', I0)", value, i
    end do

    ! get values
    do i = 1, list%get_length()
        print "('got ', F10.4, ' from ', I0)", list%get(i), i
    end do

    print '(A)', 'list:'
    call list%print_list()

    ! clear list
    call list%clear()
    print '(A)', 'list:'
    call list%print_list()

end program list_test
