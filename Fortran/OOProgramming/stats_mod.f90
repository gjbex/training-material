module stats_mod
    use, intrinsic :: iso_fortran_env, only : f8 => REAL64, i8 => INT64, &
                                              error_unit
    implicit none

    private
    type, public :: stats_type
        private
        real(kind=f8) :: sum = 0.0_f8
        integer(kind=i8) :: n = 0_i8
    contains
        procedure :: add
        procedure :: avg
    end type stats_type

    public :: new_stats

contains

    type(stats_type) function new_stats()
        implicit none
        new_stats%sum = 0.0_f8
        new_stats%n = 0_i8
    end function new_stats

    subroutine add(stats, value)
        implicit none
        class(stats_type), intent(inout) :: stats
        real(kind=f8), intent(in) :: value
        stats%sum = stats%sum + value
        stats%n = stats%n + 1
    end subroutine add

    real(kind=f8) function avg(stats)
        implicit none
        class(stats_type), intent(in) :: stats
        if (stats%n == 0) then
            write(unit=error_unit, fmt='(A)') '### error: no data for avg'
            stop
        end if
        avg = stats%sum/stats%n
    end function avg
    
end module stats_mod
