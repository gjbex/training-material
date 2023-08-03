#!/usr/bin/env python

from argparse import ArgumentParser
from Bio import SeqIO
import textwrap

def print_seq_record(seq_record, indent_with='  ', indent=''):
    print(f'Sequence ID: {seq_record.id}')
    indent += indent_with
    print('{0}Name: {1}'.format(indent, seq_record.name))
    print('{0}Description: {1}'.format(indent, seq_record.description))
    print('{0}Length: {1:d}'.format(indent, len(seq_record)))
    print('{0}Features ({1:d}):'.format(indent, len(seq_record.features)))
    for feature in seq_record.features:
        print_feature(feature, indent + indent_with)
    print('')
    print(textwrap.indent(textwrap.fill(str(seq_record.seq)), indent))

def print_feature(feature, indent=''):
    print('{0:s}Type: {1:s}'.format(indent, feature.type))
    print('{0:s}\tLocation: {1}'.format(indent, feature.location))
    for key, value in feature.qualifiers.items():
        print('{0:s}\t{1:s}: {2:s}'.format(indent, key, '; '.join(value)))

if __name__ == '__main__':
    arg_parser = ArgumentParser(description='display information on a '
                                            'sequence file')
    arg_parser.add_argument('file', help='sequence file to process')
    arg_parser.add_argument('--format', help='sequence file format')
    arg_parser.add_argument('--indent', default='  ', help='identation')
    options = arg_parser.parse_args()
    nr_seqs = 0
    for seq_record in SeqIO.parse(options.file, options.format):
        nr_seqs += 1
        print_seq_record(seq_record, options.indent, '')
    print('\n{0:d} sequence{1}'.format(nr_seqs, '' if nr_seqs == 1 else 's'))
