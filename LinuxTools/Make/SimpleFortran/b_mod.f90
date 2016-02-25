module mod_b
    implicit none

contains

    subroutine print_b(n)
        implicit none
        integer, intent(in) :: n
        print '(A, I0)', 'B: ', n
    end subroutine print_b

end module mod_b
