#!/usr/bin/env python

import csv, re, sys

if __name__ == '__main__':
    file_name = sys.argv[1]
    with open(file_name, 'rb') as csv_file:
        dialect = csv.Sniffer().sniff(csv_file.read(1024))
        regex_str = r'^\s*#\s+(.+?){0}+$'.format(dialect.delimiter)
    with open(file_name, 'r') as csv_file:
        header_bytes = 0
        for line in csv_file:
            if line.startswith('#'):
                header_bytes += len(line)
                line = re.sub(regex_str, r'\1', line.strip('\r\n'))
                print 'comment: "{0}"'.format(line)
            else:
                break
    with open(file_name, 'rb') as csv_file:
        csv_file.seek(header_bytes)
        csv_reader = csv.DictReader(csv_file, fieldnames=None,
                                    restkey='rest', restval=None,
                                    dialect=dialect)
        try:
            row = csv_reader.next()
            print 'headers: {0}'.format(':'.join(csv_reader.fieldnames))
            while row:
                print row
                row = csv_reader.next()
        except StopIteration:
            pass

