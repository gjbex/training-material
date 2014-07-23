module random_seed_mod
    implicit none
    private
    public :: init_random_seed

contains

    subroutine init_random_seed()
        implicit none
        integer :: seed_dim, clock, i
        integer, dimension(:), allocatable :: seed
        call random_seed(size=seed_dim)
        allocate(seed(seed_dim))
        call system_clock(count=clock)
        seed = clock + 37*[ (i - 1, i = 1, seed_dim) ]
        call random_seed(put=seed)
        deallocate(seed)
    end subroutine init_random_seed

end module random_seed_mod

program tree_test
use, intrinsic :: iso_fortran_env
use random_seed_mod
use node_mod
implicit none
integer, parameter :: sp = REAL32
real(kind=sp), parameter :: init_prob = 1.0_sp, factor = 0.75_sp, &
                            root_dist = 0.0_sp
class(node_type), pointer :: root => null()
integer :: status

! initialize the random number generator to get a unique sequence per run
call init_random_seed()

! initialize root node, and create a tree where each node value
! denotes a distance between it, and its parent
root => root%new()
call root%init_random(init_prob, factor, root_dist)

! print the tree
call root%show()

! copmute the number of nodes in the tree
write (unit=output_unit, fmt="(A, I3)") "node count = ", &
        root%count_nodes()

! compute the maximum distance between the root and any leaf node
write (unit=output_unit, fmt="(A, F6.3)") "max. distance =", &
        root%leaf_distance()

end program tree_test
