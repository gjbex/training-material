module particles_mod
    use, intrinsic :: iso_fortran_env, only : sp => REAL32, dp => REAL64
    use :: random_mod
    implicit none
    
    private
    type, public :: particles_type
        real(kind=dp), dimension(:), allocatable :: x, y, z, &
                                                    v_x, v_y, v_z, &
                                                    mass
        integer, dimension(:), allocatable :: charge
    end type particles_type
    public :: init_particles, print_particles, delete_particles

contains

    subroutine init_particles(p, N)
        implicit none
        type(particles_type), intent(out) :: p
        integer, intent(in) :: N
        integer :: i
        real(kind=dp) :: r

        allocate(p%x(N))
        allocate(p%y(N))
        allocate(p%z(N))
        allocate(p%v_x(N))
        allocate(p%v_y(N))
        allocate(p%v_z(N))
        allocate(p%mass(N))
        allocate(p%charge(N))

        call random_number(p%x)
        call random_number(p%y)
        call random_number(p%z)
        call random_number(p%v_x)
        call random_number(p%v_y)
        call random_number(p%v_z)
        do i = 1, N
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
        type(particles_type), intent(in) :: p
        integer, intent(in) :: i
        character(len=200) :: fmt_str = "(7(E10.3, ','), I2)"

        print fmt_str, p%x(i), p%y(i), p%z(i), &
                       p%v_x(i), p%v_y(i), p%v_z(i), &
                       p%mass(i), p%charge(i)
    end subroutine print_particle

    subroutine print_particles(p)
        implicit none
        type(particles_type), intent(in) :: p
        integer :: i, N

        print "(A, 7(',', A))", 'x', 'y', 'z', 'v_x', 'v_y', 'v_z', &
                                'mass', 'charge'
        N = size(p%x)
        do i = 1, N
            call print_particle(p, i)
        end do
    end subroutine print_particles

    subroutine delete_particles(p)
        implicit none
        type(particles_type), intent(inout) :: p
        integer :: i, N

        deallocate(p%x)
        deallocate(p%y)
        deallocate(p%z)
        deallocate(p%v_x)
        deallocate(p%v_y)
        deallocate(p%v_z)
        deallocate(p%mass)
        deallocate(p%charge)

    end subroutine delete_particles

end module particles_mod
