'''module that defines a Node class to work with trees'''


class Node(object):
    '''class representing a node in a tree'''

    def __init__(self, name):
        '''constructor, takes node's label as paramenter'''
        super(Node, self).__init__()
        self._name = name
        self._children = []

    @property
    def name(self):
        '''returns the node's label'''
        return self._name

    def children(self):
        '''iterator over the node's children'''
        return iter(self._children)

    def child(self, child_index):
        '''get the specified child of this node'''
        return self._children[child_index]

    def nr_children(self):
        '''returns the node's number of children'''
        return len(self._children)

    def is_leaf(self):
        '''checks whether the node is a leaf node'''
        return self.nr_children() == 0

    def add_child(self, child):
        '''add the given node as a child to this node'''
        self._children.append(child)

    def __str__(self):
        '''string representation for debugging'''
        return 'node "{0}" with {1} children'.format(
            self.name,
            len(self._children))
