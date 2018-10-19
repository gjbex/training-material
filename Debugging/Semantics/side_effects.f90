program side_effects
    implicit none
    integer :: value

    ! .and.
    value = 0
    if (is_true(.true., is_left=.true., is_and=.true., value=value) &
        .and. &
        is_true(.true., is_left=.false., is_and=.true., value=value)) &
        print *, 'true'
    print '("T & T = ", I0)', value

    value = 0
    if (is_true(.true., is_left=.true., is_and=.true., value=value) &
        .and. &
        is_true(.false., is_left=.false., is_and=.true., value=value)) &
        print *, 'true'
    print '("T & F = ", I0)', value

    value = 0
    if (is_true(.false., is_left=.true., is_and=.true., value=value) &
        .and. &
        is_true(.true., is_left=.false., is_and=.true., value=value)) &
        print *, 'true'
    print '("F & T = ", I0)', value

    value = 0
    if (is_true(.false., is_left=.true., is_and=.true., value=value) &
        .and. &
        is_true(.false., is_left=.false., is_and=.true., value=value)) &
        print *, 'true'
    print '("F & F = ", I0)', value

    ! .or.
    value = 0
    if (is_true(.true., is_left=.true., is_and=.false., value=value) &
        .or. &
        is_true(.true., is_left=.false., is_and=.false., value=value)) &
        print *, 'true'
    print '("T | T = ", I0)', value
    
    value = 0
    if (is_true(.true., is_left=.true., is_and=.false., value=value) &
        .or. &
        is_true(.false., is_left=.false., is_and=.false., value=value)) &
        print *, 'true'
    print '("T | F = ", I0)', value

    value = 0
    if (is_true(.false., is_left=.true., is_and=.false., value=value) &
        .or. &
        is_true(.true., is_left=.false., is_and=.false., value=value)) &
        print *, 'true'
    print '("F | T = ", I0)', value

    value = 0
    if (is_true(.false., is_left=.true., is_and=.false., value=value) &
        .or. &
        is_true(.false., is_left=.false., is_and=.false., value=value)) &
        print *, 'true'
    print '("F | F = ", I0)', value

contains

    logical function is_true(flag, is_left, is_and, value)
        implicit none
        logical, intent(in) :: flag, is_left, is_and
        integer, intent(inout) :: value
        integer :: old_value
        character(len=1) :: side
        character(len=3) :: operator
        old_value = value
        if (is_left) then
            value = 1
            side = 'L'
        else
            value = 2
            side = 'R'
        end if
        if (is_and) then
            operator = 'and'
        else
            operator = 'or'
        end if
        print '(A3, A1, ": ", I0, " -> ", I0)', operator, side, &
            old_value, value
        is_true = flag
    end function is_true

end program side_effects
