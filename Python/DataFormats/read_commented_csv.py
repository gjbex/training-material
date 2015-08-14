#!/usr/bin/env python

import csv
import re
import sys

if __name__ == '__main__':
    file_name = sys.argv[1]
    regex_str = r'^\s*#\s*(.+?)$'
    with open(file_name, 'r', newline='') as csv_file:
        header_bytes = 0
        for line in csv_file:
            if line.lstrip().startswith('#'):
                header_bytes += len(line)
                line = re.sub(regex_str, r'\1', line.strip('\r\n'))
                print('comment: "{0}"'.format(line))
            else:
                break
    with open(file_name, 'r') as csv_file:
        csv_file.seek(header_bytes)
        dialect = csv.Sniffer().sniff(csv_file.read(1024))
        csv_file.seek(header_bytes)
        csv_reader = csv.DictReader(csv_file, fieldnames=None,
                                    restkey='rest', restval=None,
                                    dialect=dialect)
        try:
            row = next(csv_reader)
            print('headers: {0}'.format(':'.join(csv_reader.fieldnames)))
            while row:
                print(row)
                row = next(csv_reader)
        except StopIteration:
            pass
