#!/usr/bin/env python

from argparse import ArgumentParser
import random
import sys
import networkx as nx


def add_edge_weights(tree):
    _add_edge_weights(tree, '1')


def _add_edge_weights(tree, node):
    for child in tree.neighbors_iter(node):
        tree[node][child]['weight'] = random.random()
        _add_edge_weights(tree, child)


def main():
    arg_parser = ArgumentParser(description='add edge weights to tree')
    arg_parser.add_argument('--input', required=True,
                            help='inpput file')
    arg_parser.add_argument('--output', required=True,
                            help='outpput file')
    arg_parser.add_argument('--seed', type=int, default=None,
                            help='seed for random number generator')
    arg_parser.add_argument('--delim', dest='delimiter', default=' ',
                            help='delimiter for edge list')
    arg_parser.add_argument('--no-data', action='store_true',
                            dest='no_data', help='show edge data')
    arg_parser.add_argument('--edge-list', action='store_true',
                            help='generate edge list output')
    options = arg_parser.parse_args()
    random.seed(options.seed)
    tree = nx.read_graphml(options.input)
    add_edge_weights(tree)
    if options.edge_list:
        nx.write_edgelist(tree, options.output,
                          delimiter=options.delimiter,
                          data=not options.no_data)
    else:
        nx.write_graphml(tree, options.output)
    return 0

if __name__ == '__main__':
    status = main()
    sys.exit(status)
