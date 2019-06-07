#!/usr/bin/env python3

from argparse import ArgumentParser
import subprocess

if __name__ == '__main__':
    arg_parser = ArgumentParser(description='string alignment tester')
    arg_parser.add_argument('file', help='file with input/output data to test')
    arg_parser.add_argument('--program', default='./string_align.exe',
                            help='path to executable to check')
    options = arg_parser.parse_args()
    with open(options.file) as file:
        count, ok_count, nok_count = 0, 0, 0
        for line in file:
            count += 1
            str1, str2, aligned1, aligned2 = line.split()
            process = subprocess.run([options.program, str1, str2],
                                      capture_output=True, text=True)
            print(process.stdout)
            a1, a2 = process.stdout.split() 
            if a1 != aligned1 or a2 != aligned2:
                nok_count += 1
                print(f'received: {a1} {a2}')
                print(f'expected: {aligned1} {aligned2}')
            else:
                ok_count += 1
    print(f'{ok_count}/{count} okay, {nok_count}/{count} not okay')
