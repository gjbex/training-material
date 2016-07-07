#!/usr/bin/env python

from argparse import ArgumentParser
from Bio import Entrez
import os

if __name__ == '__main__':
    arg_parser = ArgumentParser(description='search Entrez nucleotide DB')
    arg_parser.add_argument('--organism', default='homo sapiens',
                            help='organism to search for')
    arg_parser.add_argument('--gene', default='MLH1',
                            help='gene to search for')
    arg_parser.add_argument('--max_results', type=int, default=3,
                            help='maximum number of results')
    arg_parser.add_argument('--summary', action='store_true',
                            help='only show summary')
    options = arg_parser.parse_args()
    Entrez.email = 'geertjan.bex@uhasselt.be'
    term = '"{0}"[ORGN] AND {1}[Gene Name]'.format(options.organism,
                                                   options.gene)
    handle = Entrez.esearch(db='nucleotide', term=term,
                            retmax=options.max_results)
    record = Entrez.read(handle)
    print('total results: {0:d}'.format(int(record['Count'])))
    for seq_id in record['IdList']:
        if options.summary:
            handle = Entrez.esummary(db='nucleotide', id=seq_id)
            summary = Entrez.read(handle)
            print('ID {}:'.format(seq_id))
            print('  {}'.format(summary[0]['Title']))
            print('  Updated: {}'.format(summary[0]['UpdateDate']))
        else:
            file_name = os.path.join('Data', '{0}.gbk'.format(seq_id))
            if not os.path.isfile(file_name):
                print('fetching {0}'.format(seq_id))
                handle = Entrez.efetch(db='nucleotide', id=seq_id,
                                       rettype='gb', retmode='text')
                with open(file_name, 'w') as seq_file:
                    seq_file.write(handle.read())
                handle.close()
            else:
                print('{0} already fetched'.format(seq_id))
