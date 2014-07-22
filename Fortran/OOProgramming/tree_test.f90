program tree_test
use, intrinsic :: iso_fortran_env
use node_mod
implicit none
type(node_type) :: root
class(node_type), pointer :: node1, node2
integer :: status

call root%set_value(.true.)
node1 => root%new(.true.)
call root%set_left(node1)
node2 => node1%new(.false.)
call node1%set_left(node2)
node2 => node1%new(.true.)
call node1%set_right(node2)
node1 => root%new(.false.)
call root%set_right(node1)

call root%show()

end program tree_test
