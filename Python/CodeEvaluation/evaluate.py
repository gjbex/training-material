#!/usr/bin/env python

if __name__ == '__main__':
    from argparse import ArgumentParser
    arg_parser = ArgumentParser(description='Read and exectue Ptyhon '
                                            'source code in a local '
                                            'environment')
    arg_parser.add_argument('file', help='Python file to parse')
    options = arg_parser.parse_args()
    with open(options.file, 'r') as source_file:
        source = ''.join(source_file.readlines())
    globals = {}
    locals = {}
    exec(source, globals, locals)
    for obj, val in locals.items():
        if type(val) in [int, float, str, bool]:
            print('{0} = {1}'.format(obj, str(val)))
