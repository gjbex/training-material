module mod_a
    implicit none

contains

    subroutine print_a(n)
        implicit none
        integer, intent(in) :: n
        print '(A, I0)', 'A: ', n
    end subroutine print_a

end module mod_a
