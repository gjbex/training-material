program tree
    use :: tree_mod
    implicit none
    type(node_type), pointer :: root
    type(node_type), pointer :: node

    ! create root
    root => node%new(1.0, 3)

    ! create root's first child
    call root%set_child(1, node%new(2.0, 2))
    node => root%get_child(1)
    call node%set_child(1, node%new(3.0, 0))
    call node%set_child(2, node%new(4.0, 0))

    ! create root's second child
    call root%set_child(2, node%new(5.0, 0))

    ! create root's third child
    call root%set_child(3, node%new(6.0, 1))
    node => root%get_child(3)
    call node%set_child(1, node%new(7.0, 0))

    ! print some node's value
    node => root%get_child(1)
    node => node%get_child(2)
    print '(A, ES15.5)', 'node 1.1.2: ', &
        node%get_value()

    print '(A)', 'tree:'
    call root%show()

    call root%visit(add_one)

    print '(A)', 'transformed tree:'
    call root%show()

contains

    real function add_one(value)
        implicit none
        real, intent(in) :: value
        add_one = value + 1.0
    end function add_one

end program tree
