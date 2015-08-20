#!/usr/bin/env python

if __name__ == '__main__':
    import csv
    import sys
    file_name = sys.argv[1]
    with open(file_name, 'r') as csv_file:
        dialect = csv.Sniffer().sniff(csv_file.read(1024))
        csv_file.seek(0)
        for row in csv.reader(csv_file, dialect=dialect):
            if not row[0].startswith('#'):
                print(row)
