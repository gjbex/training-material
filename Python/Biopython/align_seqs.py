#!/usr/bin/env python

from argparse import ArgumentParser
from Bio.Align.Applications import MuscleCommandline
from Bio import SeqIO
from Bio import AlignIO
from io import StringIO


if __name__ == '__main__':
    arg_parser = ArgumentParser(description='align sequences using muscle')
    arg_parser.add_argument('file', help='sequence file')
    arg_parser.add_argument('--format', default='fasta',
                            help='input format')
    arg_parser.add_argument('--out', required=False, help='output file')
    options = arg_parser.parse_args()
    seqs = {}
    for seq_record in SeqIO.parse(options.file, options.format):
        seqs[seq_record.id] = seq_record.seq
    if options.out:
        muscle_cl = MuscleCommandline(input=options.file, out=options.out,
                                      clw=True)
        muscle_cl()
    else:
        muscle_cl = MuscleCommandline(input=options.file)
        stdout, stderr = muscle_cl()
        alignments = AlignIO.read(StringIO(stdout), 'fasta')
        print('number of alignments: {0:d}'.format(len(alignments)))
        msg = 'id: {0}\n\tlength: {1:d}\n\tgaps: {2:d}'
        for alignment in alignments:
            print(msg.format(alignment.id,
                             len(str(seqs[alignment.id])),
                             str(alignment.seq).count('-')))
