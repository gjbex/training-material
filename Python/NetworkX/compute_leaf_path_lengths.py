#!/usr/bin/env python

import networkx as nx

def is_leaf(tree, node):
    return len(tree.neighbors(node)) == 0

def leaf_path_lengths(tree):
    path_lengths = nx.shortest_path_length(tree, '1', weight='weight')
    remove = []
    for node in path_lengths:
        if not is_leaf(tree, node):
            remove.append(node)
    for node in remove:
        del path_lengths[node]
    return path_lengths

if __name__ == '__main__':

    from argparse import ArgumentParser
    from StringIO import StringIO
    import sys

    def main():
        arg_parser = ArgumentParser(description='compute leaf path lengths')
        input = StringIO(''.join(sys.stdin.readlines()))
        tree = nx.read_graphml(input)
        path_lengths = leaf_path_lengths(tree)
        for leaf in path_lengths:
            print '{0}: {1:.4f}'.format(leaf, path_lengths[leaf])
        return 0

    status = main()
    sys.exit(status)



