#!/usr/bin/env python

from argparse import ArgumentParser
import sys
import networkx as nx


def is_leaf(tree, node):
    return len(tree.neighbors(node)) == 0


def leaf_path_lengths(tree):
    path_lengths = nx.shortest_path_length(tree, '1', weight='weight')
    remove = [node for node in path_lengths if not is_leaf(tree, node)]
    for node in remove:
        del path_lengths[node]
    return path_lengths


def main():
    arg_parser = ArgumentParser(description='compute leaf path lengths')
    arg_parser.add_argument('--input', required=True, help='input file')
    options = arg_parser.parse_args()
    tree = nx.read_graphml(options.input)
    path_lengths = leaf_path_lengths(tree)
    for leaf in path_lengths:
        print('{0}: {1:.4f}'.format(leaf, path_lengths[leaf]))
    return 0

if __name__ == '__main__':
    status = main()
    sys.exit(status)
