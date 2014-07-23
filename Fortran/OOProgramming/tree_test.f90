program tree_test
use, intrinsic :: iso_fortran_env
use node_mod
implicit none
integer, parameter :: sp = REAL32
class(node_type), pointer :: root => null(), node1, node2
integer :: status, seed_dim, clock, i
integer, dimension(:), allocatable :: seed
character(len=10) :: buffer

call random_seed(size=seed_dim)
allocate(seed(seed_dim))
call system_clock(count=clock)
seed = clock + 37*[ (i - 1, i = 1, seed_dim) ]
call random_seed(put=seed)
deallocate(seed)

root => root%new()
call root%init_random(1.0, 0.75, 0.0)

call root%show()

write (unit=output_unit, fmt="(A, I3)") "node count = ", &
        root%count_nodes()
write (unit=output_unit, fmt="(A, F6.3)") "max. distance =", &
        root%leaf_distance()
end program tree_test
