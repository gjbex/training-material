#!/usr/bin/env python

from argparse import ArgumentParser
import random
import sys
import networkx as nx


def random_tree(max_branch, max_height):
    G = nx.DiGraph()
    random_subtree(G, None, max_branch, max_height)
    return G


def random_subtree(G, root, max_branch, max_height):
    if max_height:
        if root:
            nr_branches = random.randrange(0, max_branch + 1)
            for i in range(1, nr_branches + 1):
                node = root + '.' + str(i)
                G.add_edge(root, node)
                random_subtree(G, node, max_branch, max_height - 1)
        else:
            node = '1'
            random_subtree(G, node, max_branch, max_height - 1)


def main():
    arg_parser = ArgumentParser(description='generate random tree')
    arg_parser.add_argument('--output', required=True,
                            help='output file name')
    arg_parser.add_argument('--branching', dest='max_branch', type=int,
                            default=3, help='maximum node branching')
    arg_parser.add_argument('--height', dest='max_height', type=int,
                            default=4, help='maximum tree height')
    arg_parser.add_argument('--seed', type=int, default=None,
                            help='seed for random number generator')
    arg_parser.add_argument('--delim', dest='delimiter', default=' ',
                            help='delimiter for edge list')
    arg_parser.add_argument('--no-data', action='store_true',
                            dest='no_data', help='show edge data')
    arg_parser.add_argument('--edge-list', action='store_true',
                            dest='edge_list',
                            help='generate edge list output')
    options = arg_parser.parse_args()
    random.seed(options.seed)
    tree = random_tree(options.max_branch, options.max_height)
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
