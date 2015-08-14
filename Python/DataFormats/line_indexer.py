#!/usr/bin/env python

if __name__ == '__main__':
    from argparse import ArgumentParser, FileType
    import csv
    import sys
    arg_parser = ArgumentParser(description='create a CSV file with start '
                                            'line positions and line '
                                            'lengths for a given file')
    arg_parser.add_argument('input_file', type=FileType('rb'),
                            help='file to index')
    arg_parser.add_argument('--output_file', type=FileType('w'),
                            help='CSV output file')
    arg_parser.add_argument('--no_header', action='store_true',
                            help='do not add header row to CSV file')
    options = arg_parser.parse_args()
    if options.output_file:
        csv_writer = csv.writer(options.output_file)
    else:
        csv_writer = csv.writer(sys.stdout)
    if not options.no_header:
        csv_writer.writerow(['position', 'line_length'])
    c = options.input_file.read(1)
    length = 0
    pos = 0
    line_pos = 0
    while c:
        pos += 1
        if c == b'\r':
            pass
        elif c == b'\n':
            csv_writer.writerow([line_pos, length])
            length = 0
            line_pos = pos
        else:
            length += 1
        c = options.input_file.read(1)
