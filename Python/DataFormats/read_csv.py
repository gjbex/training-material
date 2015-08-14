#!/usr/bin/env python

import csv
from argparse import ArgumentParser


def main():
    arg_parser = ArgumentParser(description='reads csv file, summarize')
    arg_parser.add_argument('--file', type=str, action='store',
                            dest='file', help='CSV file to parse')
    options = arg_parser.parse_args()
    with open(options.file, 'r') as csv_file:
        dialect = csv.Sniffer().sniff(csv_file.read(1024))
        csv_file.seek(0)
        sum = 0.0
        csv_reader = csv.DictReader(csv_file, fieldnames=None,
                                    restkey='rest', restval=None,
                                    dialect=dialect)
        print('headers: {0}'.format(':'.join(csv_reader.fieldnames)))
        for row in csv_reader:
            print('{name} --- {weight}'.format(name=row['name'],
                                               weight=row['weight']))
            sum += float(row['weight'])
        print('sum = {}'.format(sum))

if __name__ == '__main__':
    main()
