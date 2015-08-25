#!/usr/bin/env python
'''module containing various functions for working with trees and nodes'''

from node_parser import NodeParser
import unittest


def depth(node):
    '''compute the depth of the given tree'''
    if node is None:
        return 0
    elif node.is_leaf():
        return 1
    else:
        return 1 + max(list(map(depth, node.children())))


def depth_first_iterator(node):
    '''returns an depth-first itreator over the node and its children'''
    if node is not None:
        node_stack = [(node, -1)]
        while len(node_stack) > 0:
            node, child_index = node_stack.pop()
            if child_index == -1:
                if not node.is_leaf():
                    node_stack.append((node, child_index + 1))
                yield node
            elif child_index < node.nr_children():
                node_stack.append((node, child_index + 1))
                node_stack.append((node.child(child_index), -1))


def nr_leaf_nodes(start_node):
    '''returns the number of leaf nodes starting form the given node'''
    nr = 0
    for node in depth_first_iterator(start_node):
        if node.is_leaf():
            nr += 1
    return nr


class DepthTest(unittest.TestCase):

    def test_empty_tree(self):
        parser = NodeParser()
        parser.parse('()')
        tree = parser.node()
        self.assertEqual(depth(tree), 0)

    def test_single_node(self):
        parser = NodeParser()
        parser.parse('(c1)')
        tree = parser.node()
        self.assertEqual(depth(tree), 1)

    def test_tree(self):
        parser = NodeParser()
        parser.parse('(c1 ((c2) (c3 ((c4) (c5))) (c6)))')
        tree = parser.node()
        self.assertEqual(depth(tree), 3)

    def test_deep_tree(self):
        parser = NodeParser()
        parser.parse('(c1 ((c2 ((c3 ((c4)))))))')
        tree = parser.node()
        self.assertEqual(depth(tree), 4)


class DepthFirstIteratorTest(unittest.TestCase):

    def test_empty_tree(self):
        parser = NodeParser()
        parser.parse('()')
        tree = parser.node()
        nodes = []
        for node in depth_first_iterator(tree):
            nodes.append(node.name)
        self.assertEqual(nodes, [])

    def test_single_node(self):
        parser = NodeParser()
        parser.parse('(c1)')
        tree = parser.node()
        nodes = []
        for node in depth_first_iterator(tree):
            nodes.append(node.name)
        self.assertEqual(nodes, ['c1'])

    def test_tree(self):
        parser = NodeParser()
        parser.parse('(c1 ((c2) (c3 ((c4) (c5))) (c6)))')
        tree = parser.node()
        nodes = []
        for node in depth_first_iterator(tree):
            nodes.append(node.name)
        self.assertEqual(nodes, ['c1', 'c2', 'c3', 'c4', 'c5', 'c6'])

    def test_deep_tree(self):
        parser = NodeParser()
        parser.parse('(c1 ((c2 ((c3 ((c4)))))))')
        tree = parser.node()
        nodes = []
        for node in depth_first_iterator(tree):
            nodes.append(node.name)
        self.assertEqual(nodes, ['c1', 'c2', 'c3', 'c4'])


class NrLeafsTest(unittest.TestCase):

    def test_empty_tree(self):
        parser = NodeParser()
        parser.parse('()')
        tree = parser.node()
        self.assertEqual(nr_leaf_nodes(tree), 0)

    def test_single_node(self):
        parser = NodeParser()
        parser.parse('(c1)')
        tree = parser.node()
        self.assertEqual(nr_leaf_nodes(tree), 1)

    def test_tree(self):
        parser = NodeParser()
        parser.parse('(c1 ((c2) (c3 ((c4) (c5))) (c6)))')
        tree = parser.node()
        self.assertEqual(nr_leaf_nodes(tree), 4)

    def test_deep_tree(self):
        parser = NodeParser()
        parser.parse('(c1 ((c2 ((c3 ((c4)))))))')
        tree = parser.node()
        self.assertEqual(nr_leaf_nodes(tree), 1)

if __name__ == '__main__':
    unittest.main()
