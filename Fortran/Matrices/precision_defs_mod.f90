module precision_defs
    use, intrinsic :: iso_fortran_env, only : REAL32, REAL64
    implicit none
    private
    integer, parameter, public :: sp = REAL32
    integer, parameter, public :: dp = REAL64

end module precision_defs
