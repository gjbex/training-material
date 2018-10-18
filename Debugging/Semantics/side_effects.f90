program side_effects
    implicit none
    integer :: value = 0
    if (is_a(value) .or. is_b(value)) &
        print '(A, I0)', 'a or b: ', value
    if (is_b(value) .or. is_a(value)) &
        print '(A, I0)', 'b or a: ', value
    if (is_a(value) .and. is_b(value)) &
        print '(A, I0)', 'a and b: ', value
    if (is_b(value) .and. is_a(value)) &
        print '(A, I0)', 'b and a: ', value

contains

    logical function is_a(value)
        implicit none
        integer, intent(inout) :: value
        value = 1
        is_a = .true.
    end function is_a

    logical function is_b(value)
        implicit none
        integer, intent(inout) :: value
        value = 2
        is_b = .true.
    end function is_b

end program side_effects
