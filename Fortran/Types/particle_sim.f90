program particle_sim
use, intrinsic :: iso_fortran_env
use particles_mod
implicit none
integer, parameter :: N = 4
type(particles) :: p

call init_particles(p, N)
call print_particles(p)
call delete_particles(p)

end program particle_sim
