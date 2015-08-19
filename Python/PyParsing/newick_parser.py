#!/usr/bin/env python
'''parser for Newick tree-structured data'''

import node
import node_parser
from pyparsing import (alphanums, Literal, Word, Group, Forward, Regex,
                       delimitedList)


class NewickNode(node.Node):
    '''Class representing nodes in a Newick encoded tree'''

    _node_id = 0

    def __init__(self, name=None):
        '''Constructor'''
        if name is None:
            NewickNode._node_id += 1
            name = 'node_{0:03d}'.format(NewickNode._node_id)
        super(NewickNode, self).__init__(name)
        self._label = None
        self._length = None

    @property
    def label(self):
        '''Get the node's label'''
        return self._label

    @label.setter
    def label(self, label):
        '''Sets the node's label'''
        self._label = label

    @property
    def length(self):
        '''Get the length of this node'''
        return self._length

    @length.setter
    def length(self, length):
        '''Sets the length for the node'''
        self._length = length


class NewickParser(object):
    '''Class implementing a Newick data parser'''

    def __init__(self):
        '''Constructor for parser'''
        super(NewickParser, self).__init__()
        self._define_grammer()

    def _define_grammer(self):
        '''Define the grammar to be used, and add the various actions'''
        taxa = Word(alphanums).setResultsName('taxa_name')
        length = Regex(r'(\d+\.\d+)').setResultsName('length')
        lb = Literal('(').suppress()
        rb = Literal(')').suppress()
        end = Literal(';').suppress()
        length_sep = Literal(':').suppress()
        leaf = taxa + length_sep + length
        node = Forward()
        siblings = Group(delimitedList(node, ',')).setResultsName('children')
        children = lb + siblings + rb + length_sep + length
        node << (leaf | children)
        tree = lb + siblings + rb + end
        self._grammar = tree

        def leaf_action(toks):
            '''create a node, and add label and length'''
            leaf_node = NewickNode()
            leaf_node.label = toks['taxa_name']
            leaf_node.length = float(toks['length'])
            return leaf_node

        def children_action(toks):
            '''create a node, add children and length'''
            parent_node = NewickNode()
            if 'length' in list(toks.keys()):
                parent_node.length = float(toks['length'])
            for child in toks['children']:
                parent_node.add_child(child)
            return parent_node
        leaf.addParseAction(leaf_action)
        children.addParseAction(children_action)
        tree.addParseAction(children_action)

    def parse(self, str):
        '''Parse the node or tree encoded by the given string'''
        return self._grammar.parseString(str)[0]


def main():
    tree_str = '(c1 ((c2) (c3 ((c4) (c5))) (c6)))'
    parser = node_parser.NodeParser()
    results = parser.parse(tree_str)
    print(results)
    print(parser.node())

if __name__ == '__main__':
    main()
