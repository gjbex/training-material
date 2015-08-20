#!/usr/bin/env python

from argparse import ArgumentParser, FileType
from newick_parser import NewickParser


def compute_branch_lengths(node, branch_lengths=None, length=0.0):
    if branch_lengths is None:
        branch_lengths = {}
        compute_branch_lengths(node, branch_lengths, length)
        return branch_lengths
    if node.is_leaf():
        branch_lengths[node.label] = length + node.length
    else:
        if node.length is not None:
            length += node.length
        for child in node.children():
            compute_branch_lengths(child, branch_lengths, length)


def main():
    arg_parser = ArgumentParser(description='Determine leaf branch '
                                            'lengths for Newick tree.')
    arg_parser.add_argument('--file', type=FileType('r'), action='store',
                            dest='file', required=True,
                            help='Newick file to parse')
    options = arg_parser.parse_args()
    tree_str = '\n'.join(options.file.readlines())
    options.file.close()
    node_parser = NewickParser()
    tree = node_parser.parse(tree_str)
    branch_lengths = compute_branch_lengths(tree)
    for taxa, length in list(branch_lengths.items()):
        print('{taxa}: {length}'.format(taxa=taxa, length=length))

if __name__ == '__main__':
    main()
