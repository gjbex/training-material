program alignment
    implicit none
    integer :: v1, v2, v_a1, v_a2
    !dir$ attributes align:16 :: v_a1, v_a2
    character(len=80) :: fmt_str = '(A, 2(/, T4, I0), /, T4, A, I0, A)'
    print fmt_str, 'not aligned:', loc(v1), loc(v2), 'diff: ', loc(v2) - loc(v1), ' byte'
    print fmt_str, 'aligned:', loc(v_a1), loc(v_a2), 'diff: ', loc(v_a2) - loc(v_a1), ' byte'
end program alignment
