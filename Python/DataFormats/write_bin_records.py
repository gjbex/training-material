#!/usr/bin/env python

from argparse import ArgumentParser
from struct import pack

def write_record(out_file, name, age):
    buffer = pack('8si', bytes(name, 'ascii'), age)
    out_file.write(buffer)

if __name__ == '__main__':
    arg_parser = ArgumentParser(description='write binary record data')
    arg_parser.add_argument('file', help='file to write to')
    options = arg_parser.parse_args()
    people = [
        ('alice', 34),
        ('bob', 32),
        ('carol', 28),
        ('darren', 29),
        ('methusalem', 103),
    ]
    with open(options.file, 'wb') as bin_file:
        for name, age in people:
            write_record(bin_file, name, age)
            print(f'{name:10s} {age:d}')
