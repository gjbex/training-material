#!/usr/bin/env python

from argparse import ArgumentParser
from Bio import Entrez
from operator import attrgetter

if __name__ == '__main__':
    arg_parser = ArgumentParser(description='get info on Entrez databases')
    arg_parser.add_argument('db', nargs='?', help='database name')
    arg_parser.add_argument('--email', default='geertjan.bex@uhasselt.be',
                            help='email address to use')
    arg_parser.add_argument('--fields', action='store_true',
                            help='show database fields information')
    options = arg_parser.parse_args()
    Entrez.email = options.email
    if options.db:
        with Entrez.einfo(db=options.db) as handle:
            record = Entrez.read(handle)
            db_info = record['DbInfo']
            print(db_info['Description'])
            print('Count: {}'.format(db_info['Count']))
            print('Last update: {}'.format(db_info['LastUpdate']))
            if options.fields:
                print('Fields:')
                fmt_str = '{Name} ({FullName}): {Description}'
                for field in sorted(db_info['FieldList'],
                                    key=lambda x: x['Name']):
                    print(fmt_str.format(**field))
    else:
        with Entrez.einfo() as handle:
            record = Entrez.read(handle)
            for db_name in sorted(record['DbList']):
                print(db_name)
