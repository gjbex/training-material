#!/usr/bin/env python
'''module to parse a line of data into its fields'''

def parse_line(line):
    '''Split a line into its fields, convert to the appropriate types,
       and return as a tuple.
       >>> parse_line('5  3  3.7')
       (5, 3, 3.7)
       >>> parse_line('5 3 3')
       (5, 3, 3)
      '''
    data = line.rstrip('\r\n').split()
    return (int(data[0]), int(data[1]), float(data[2]))

# if __name__ == '__main__':
#     import doctest
#     doctest.testmod()

