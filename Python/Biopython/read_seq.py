#!/usr/bin/env python

from argparse import ArgumentParser
from Bio import SeqIO, SeqUtils
from collections import namedtuple

SeqStats = namedtuple('SeqStats', ['length', 'gc', 'weight'])


def compute_stats(seq):
    stats = SeqStats
    stats.length = len(seq)
    stats.gc = SeqUtils.GC(seq)
    try:
        stats.weight = SeqUtils.molecular_weight(seq)
    except ValueError:
        stats.weight = None
    return stats

if __name__ == '__main__':
    arg_parser = ArgumentParser(description='Read sequence file and '
                                            'compute some statistics')
    arg_parser.add_argument('file', help='sequence file to parse')
    arg_parser.add_argument('--format', default='fasta', help='file format')
    options = arg_parser.parse_args()
    seqs = {
        seq_record.id: seq_record.seq
        for seq_record in SeqIO.parse(options.file, options.format)
    }
    fmt_str = ('id: {id}\n\t'
               'length: {stats.length}\n\t'
               'gc: {stats.gc}\n\t'
               'molecular weight: {stats.weight}')
    for id, seq in seqs.items():
        seq_stats = compute_stats(seq)
        print(fmt_str.format(id=id, stats=seq_stats))
    print('{0:d} sequences'.format(len(seqs)))
