program list_test
    use linked_list_mod
    use, intrinsic :: iso_fortran_env, only : dp => REAL64
    implicit none
    type(list_type) :: list
    integer, parameter :: nr_values = 10
    integer :: i
    real(kind=dp), dimension(nr_values) :: values
    real(kind=dp) :: value
    
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

end program list_test
