program tree_test
use, intrinsic :: iso_fortran_env
use random_mod
use node_mod
implicit none
integer, parameter :: sp = REAL32
real(kind=sp), parameter :: init_prob = 1.0_sp, factor = 0.75_sp, &
                            root_dist = 0.0_sp
type(node_type) :: root

! initialize the random number generator to get a unique sequence per run
call init_random_seed()

! initialize root node, and create a tree where each node value
! denotes a distance between it, and its parent
call root%init_random(init_prob, factor, root_dist)

! print the tree
call root%show()

! compute the number of nodes in the tree
write (unit=output_unit, fmt="(A, I3)") "node count = ", &
        root%count_nodes()

! compute the maximum distance between the root and any leaf node
write (unit=output_unit, fmt="(A, F6.3)") "max. distance =", &
        root%leaf_distance()

end program tree_test
