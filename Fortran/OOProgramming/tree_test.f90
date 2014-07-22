program tree_test
use, intrinsic :: iso_fortran_env
use node_mod
implicit none
type(node_type) :: root
type(node_type), pointer :: node
integer :: status

call root%set(.false.)
allocate(node, source=node_type(.true.), stat=status)
if (status /= 0) then
    write (unit=error_unit, fmt="(A)") "# error: can not allocate node"
end if
call root%add_left(node)
allocate(node, source=node_type(.false.), stat=status)
if (status /= 0) then
    write (unit=error_unit, fmt="(A)") "# error: can not allocate node"
end if
call root%add_right(node)

call root%show()

end program tree_test
