#!/usr/bin/env python

from argparse import ArgumentParser
from multiprocessing import Pool
import networkx as nx

pool = Pool(processes=2)


def _is_leaf(tree, node):
    return len(tree.neighbors(node)) == 0


def _leaf_path_lengths(tree, node):
    global pool
    if _is_leaf(tree, node):
        return {node: 0.0}
    else:
        path_lengths = {}
        results = {}
        for child in tree.neighbors_iter(node):
            results[child] = _leaf_path_lengths(tree, child)
        for child in tree.neighbors_iter(node):
            weight = tree[node][child]['weight']
#            lengths = results[child].get()
            lengths = results[child]
            for leaf in lengths:
                path_lengths[leaf] = lengths[leaf] + weight
        return path_lengths


def leaf_path_lengths(tree):
    return _leaf_path_lengths(tree, '1')

if __name__ == '__main__':
    arg_parser = ArgumentParser(description='compute leaf path lengths')
    arg_parser.add_argument('--input', required=True, help='input file')
    arg_parser.add_argument('--pool-size', default=1,
                            dest='pool_size', type=int,
                            help='pool size for parallel processing')
    options = arg_parser.parse_args()
    tree = nx.read_graphml(options.input)
    path_lengths = leaf_path_lengths(tree)
    for leaf in path_lengths:
        print('{0}: {1:.4f}'.format(leaf, path_lengths[leaf]))
