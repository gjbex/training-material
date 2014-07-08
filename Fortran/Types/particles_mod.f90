module particles_mod
    use, intrinsic :: iso_fortran_env
    implicit none
    
    private
    integer, parameter, public :: sp = REAL32, dp = REAL64
    type, public :: particles
        real(kind=dp), dimension(:), allocatable :: x, y, z, mass
        integer, dimension(:), allocatable :: charge
    end type particles
    public :: init_particles, print_particles, delete_particles

contains

    subroutine init_particles(p, N)
        implicit none
        type(particles), intent(out) :: p
        integer, intent(in) :: N
        integer :: i
        real(kind=dp) :: r

        allocate(p%x(N))
        allocate(p%y(N))
        allocate(p%z(N))
        allocate(p%mass(N))
        allocate(p%charge(N))

        do i = 1, N
            call random_number(r)
            p%x(i) = r
            call random_number(r)
            p%y(i) = r
            call random_number(r)
            p%z(i) = r
            call random_number(r)
            p%mass(i) = r
            call random_number(r)
            if (r < 0.5) then
                p%charge(i) = -1
            else
                p%charge(i) = 1
            end if
        end do
    
    end subroutine init_particles

    subroutine print_particle(p, i)
        implicit none
        type(particles), intent(in) :: p
        integer, intent(in) :: i
        character(len=80) :: fmt_str = "('(', E10.3, ',', E10.3, ',', E10.3 ')', ': ', E10.3, ',', I2)"

        print fmt_str, p%x(i), p%y(i), p%z(i), p%mass(i), p%charge(i)

    end subroutine print_particle

    subroutine print_particles(p)
        implicit none
        type(particles), intent(in) :: p
        integer :: i, N

        N = size(p%x)
        do i = 1, N
            call print_particle(p, i)
        end do

    end subroutine print_particles

    subroutine delete_particles(p)
        implicit none
        type(particles), intent(inout) :: p
        integer :: i, N

        deallocate(p%x)
        deallocate(p%y)
        deallocate(p%z)
        deallocate(p%mass)
        deallocate(p%charge)

    end subroutine delete_particles

end module particles_mod
