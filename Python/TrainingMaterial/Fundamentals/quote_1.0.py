#!/usr/bin/env python

import sys

def main():
    file_name = sys.argv[1]
    with open(file_name) as in_file:
        for line in in_file:
            print '|{0}|'.format(line.rstrip('\r\n'))
    return 0

if __name__ == '__main__':
    status = main()
    sys.exit(status)

