'''parser for tree-structured data'''

from pyparsing import (Forward, Word, alphas, alphanums, Literal,
                       Optional, ZeroOrMore, Group)
from node import Node


class NodeParser:
    '''Class implementing tree structured data parser, data is of the form
       (c1 ((c2) (c3 ((c4) (c5))) (c6)))'''

    def __init__(self):
        '''Constructor for parser'''
        self._current_node = None
        self._node_stack = []
        self._define_grammer()

    def _define_actions(self):
        '''Internal method to define the various parse actions by currying
           with parser object.  To be called from grammar initializing
           method'''
        self._name_action = lambda toks: self._create_node(toks)
        self._clb_action = lambda: self._push_current()
        self._crb_action = lambda: self._pop_current()

    def _define_grammer(self):
        '''Define the grammar to be used, and add the various actions'''
        self._define_actions()
        node_name = Word(alphas, alphanums)
        lb = Literal('(').suppress()
        clb = Literal('(').suppress()
        rb = Literal(')').suppress()
        crb = Literal(')').suppress()
        node = Forward()
        children = clb + Group(ZeroOrMore(node)) + crb
        node << lb + node_name + Optional(children) + rb
        empty_tree = lb + rb
        tree = node | empty_tree
        self._grammar = tree
        node_name.addParseAction(self._name_action)
        clb.addParseAction(self._clb_action)
        crb.addParseAction(self._crb_action)

    def _create_node(self, toks):
        '''Action when a new node definition is encountered, creates a new
           Node object'''
        self._current_node = Node(toks[0])
        depth = len(self._node_stack)
        if depth > 0:
            self._node_stack[depth - 1].add_child(self._current_node)

    def _push_current(self):
        '''Action to be performed when a node defines children'''
        self._node_stack.append(self._current_node)
        self._current_node = None

    def _pop_current(self):
        '''Action to be performed at end of a node's children definition'''
        self._current_node = self._node_stack.pop()

    def parse(self, str):
        '''Parse the node or tree encoded by the given string'''
        return self._grammar.parseString(str)

    def node(self):
        '''Returns the Node object representing the root of the tree that
           was just parsed'''
        return self._current_node
