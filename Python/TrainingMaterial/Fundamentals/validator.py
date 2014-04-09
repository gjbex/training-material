#!/usr/bin/env python

import sys

def validate(case_nr, dim_nr, temp):
    if dim_nr == 3 and temp < 0.0:
        sys.stderr.write('# error in case {0}\n'.format(case_nr))
        return False
    else:
        return True

def parse_line(line):
    '''Split a line into its fields, convert to the appropriate types,
       and return as a tuple.'''
    data = line.rstrip('\r\n').split()
    return (int(data[0]), int(data[1]), float(data[2]))

def main():
    sys.stdin.readline()
    for line in sys.stdin:
        (case_nr, dim_nr, temp) = parse_line(line)
        validate(case_nr, dim_nr, temp)

if __name__ == '__main__':
    main()

