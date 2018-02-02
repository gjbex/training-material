program avg_path_test
use, intrinsic :: iso_fortran_env
use random_mod
use node_mod
implicit none
integer, parameter :: sp = REAL32
integer :: nr_trees = 1000
real(kind=sp), parameter :: init_prob = 1.0_sp, factor = 0.75_sp, &
                            root_dist = 0.0_sp
type(node_type) :: root
integer :: i
real(kind=sp) :: avg_path, avg_nodes
character(len=20) :: buffer

if (command_argument_count() > 0) then
    call get_command_argument(1, buffer)
    read (buffer, "(I10)") nr_trees
end if

! initialize the random number generator to get a unique sequence per run
call init_random_seed()

avg_path = 0.0_sp
avg_nodes = 0.0_sp
do i = 1, nr_trees
    ! create a tree where each node value
    ! denotes a distance between it, and its parent
    call root%init_random(init_prob, factor, root_dist)
    ! compute the number of nodes in the tree, and the longest apth
    avg_path = avg_path + root%leaf_distance()
    avg_nodes = avg_nodes + root%count_nodes()
    ! finalize to prevent memory leakes
    call root%finalize()
end do
avg_path = avg_path/nr_trees
avg_nodes = avg_nodes/nr_trees

! write results
write (unit=output_unit, fmt="(A, F6.3)") "avg. path = ", avg_path
write (unit=output_unit, fmt="(A, F6.2)") "avg. nodes = ", avg_nodes

end program avg_path_test

