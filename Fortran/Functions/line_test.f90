program line_test
    use types_mod, only : sp
    use line_mod
    implicit none
    integer, parameter :: nr_points = 5
    real(kind=sp), dimension(nr_points) :: x, y, y_exp
    logical, dimension(nr_points) :: is_on_line
    integer :: i

    x = [(real(i, kind=sp), i = -2, 2)]
    y = [2.0_sp, 2.5_sp, 3.001_sp, 3.5_sp, 4.0_sp]
    y_exp = line(x)
    is_on_line = on_line(x, y)
    print '(A, E10.2)', 'epsilon = ', get_epsilon()
    do i = 1, nr_points
        print '(3F10.4, L10)', x(i), y(i), y_exp(i), is_on_line(i)
    end do
    if (all(is_on_line)) print '(A)', '# all on line'
    if (any(is_on_line)) print '(A)', '# some on line'

    call set_epsilon(1.0e-2_sp)
    is_on_line = on_line(x, y)
    print '(A, E10.2)', 'epsilon = ', get_epsilon()
    do i = 1, nr_points
        print '(3F10.4, L10)', x(i), y(i), y_exp(i), is_on_line(i)
    end do
    if (all(is_on_line)) print '(A)', '# all on line'
    if (any(is_on_line)) print '(A)', '# some on line'

end program line_test
