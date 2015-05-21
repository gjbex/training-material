module quad_mod
    implicit none

    private
    public :: quad
    
contains

    function quad(f, a, b) result(q_f)
        use :: types_mod, only : dp
        use :: quad_func_interface
        implicit none
        procedure(quad_func_type) :: f
        real(kind=dp), intent(in) :: a, b
        real(kind=dp) :: q_f
        q_f = (f(b) + f(a))*(b - a)
    end function quad
        
end module quad_mod
