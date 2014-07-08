program particle_sim
use, intrinsic :: iso_fortran_env
use particles_mod
implicit none
integer :: N = 20
type(particles) :: p
character(len=128) :: buffer

if (command_argument_count() >= 1) then
    call get_command_argument(1, buffer)
    read (buffer, "(I5)") N
end if
call init_particles(p, N)
call print_particles(p)
call delete_particles(p)

end program particle_sim
