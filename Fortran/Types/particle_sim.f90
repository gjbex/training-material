program particle_sim
    use particles_mod, only : particles_type, init_particles, &
                              print_particles, delete_particles
    implicit none
    integer :: N = 20
    type(particles_type) :: p
    character(len=128) :: buffer

    if (command_argument_count() >= 1) then
        call get_command_argument(1, buffer)
        read (buffer, "(I5)") N
    end if
    call init_particles(p, N)
    call print_particles(p)
    call delete_particles(p)

end program particle_sim
