#!/usr/bin/env python

from argparse import ArgumentParser
from Bio import SeqIO
from Bio.Blast import NCBIWWW, NCBIXML


if __name__ == '__main__':
    arg_parser = ArgumentParser(description='perform a BLAST search')
    arg_parser.add_argument('file', help='FASTA file with the seequence '
                                         'to search, or BLAST result '
                                         'file to be parsed')
    arg_parser.add_argument('--save', action='store_true',
                            help='save search results to a file for '
                                 'reuse')
    arg_parser.add_argument('--format', choices=['fasta', 'xml'],
                            default='xml',
                            help='indicates whether to search, or use '
                                 'a saved search result')
    arg_parser.add_argument('--e_val', type=float, default=0.04,
                            help='E value threshold to use')
    options = arg_parser.parse_args()
    if options.format == 'fasta':
        seq_record = SeqIO.read(options.file, format='fasta')
        result_handle = NCBIWWW.qblast('blastn', 'nt',
                                       seq_record.format('fasta'))
        if options.save:
            out_file_name = '{0}.xml'.format(options.file)
            with open(out_file_name, 'w') as out_file:
                out_file.write(result_handle.read())
            result_handle = open(out_file_name, 'r')
    else:
        result_handle = open(options.file, 'r')
    blast_records = NCBIXML.parse(result_handle)
    nr_records = 0
    nr_hasps = 0
    for blast_record in blast_records:
        nr_records += 1
        for alignment in blast_record.alignments:
            for hsp in alignment.hsps:
                if hsp.expect < options.e_val:
                    nr_hasps += 1
                    print('sequence: {0}'.format(alignment.title))
                    print('  length: {0:d}'.format(alignment.length))
                    print('  E value: {0:.3e}'.format(hsp.expect))
                    print('  score: {0:.3e}'.format(hsp.score))
                    print('  {0}...'.format(hsp.query[:70]))
                    print('  {0}...'.format(hsp.match[:70]))
                    print('  {0}...\n'.format(hsp.sbjct[:70]))
    print('nr. records: {0:d}'.format(nr_records))
    print('nr. HSPs: {0:d}'.format(nr_hasps))
