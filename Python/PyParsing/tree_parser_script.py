#!/usr/bin/env python
'''parser for tree-structured data'''

from pyparsing import (Forward, Word, alphas, alphanums, Literal,
                       Optional, ZeroOrMore, Group)
from node import Node
from tree_converter import IndentedStringWriter

level = 0
current_node = None
node_stack = []


def incr_level():
    global level
    level += 1


def decr_level():
    global level
    level -= 1


def show_level(toks):
    print('{0}: level {1}'.format(toks[0], level))


def create_node(toks):
    global current_node, node_stack
    current_node = Node(toks[0])
    if len(node_stack) > 0:
        node_stack[len(node_stack) - 1].add_child(current_node)


def push_current():
    global current_node, node_stack
    node_stack.append(current_node)
    current_node = None


def pop_current():
    global current_node, node_stack
    current_node = node_stack.pop()

node_name = Word(alphas, alphanums)
node_name.addParseAction(create_node)
lb = Literal('(').suppress()
clb = Literal('(').suppress()
clb.addParseAction(push_current)
rb = Literal(')').suppress()
crb = Literal(')').suppress()
crb.addParseAction(pop_current)
node = Forward()
children = clb + Group(ZeroOrMore(node)) + crb
node << lb + node_name + Optional(children) + rb

tree_str = '(c1 ((c2) (c3 ((c4) (c5))) (c6)))'

results = node.parseString(tree_str)
print(results)
writer = IndentedStringWriter()
print(writer.write(current_node))
