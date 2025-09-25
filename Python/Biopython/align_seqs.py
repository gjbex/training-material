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
    arg_parser.add_argument('--alignment', help='input file is an '
                                                'alignment')
    arg_parser.add_argument('--show', action='store_true',
                            help='show MUSCLE output')
    options = arg_parser.parse_args()
    seqs = {
        seq_record.id: seq_record.seq
        for seq_record in SeqIO.parse(options.file, options.format)
    }
    if options.alignment:
        with open(options.alignment, 'r') as alignment_file:
            stdout = alignment_file.read()
    else:
        muscle_cl = MuscleCommandline(input=options.file)
        stdout, stderr = muscle_cl()
    if options.show:
        print(stdout)
    else:
        alignment = AlignIO.read(StringIO(stdout), 'fasta')
        print('number of sequences: {0:d}'.format(len(alignment)))
        print('length: {0:d}'.format(alignment.get_alignment_length()))
        msg = 'id: {0}\n\tlength: {1:d}\n\tgaps: {2:d}\n\ttotal: {3:d}'
        for seq_rec in alignment:
            seq_length = len(seqs[seq_rec.id])
            nr_gaps = str(seq_rec.seq).count('-')
            print(msg.format(seq_rec.id, seq_length, nr_gaps,
                             seq_length + nr_gaps))
        for seq_rec in alignment:
            print(seq_rec.seq[:76])
