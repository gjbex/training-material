#!/usr/bin/env python

import click
import sys

CONTEXT_SETTINGS = {
    'help_option_names': ('-h', '--help'),
}


def check_valid(n):
    if n < 1000 or n > 9999:
        print('Error: argument must have four digits', file=sys.stderr)
        sys.exit(1)
    if len(set(str(n))) < 2:
        print('Error: argument must have at least two distinct digits',
              file=sys.stderr)
        sys.exit(2)


def compute_sorted(n, reverse=True):
    return int(''.join(sorted(str(n), reverse=reverse)))


@click.command(context_settings=CONTEXT_SETTINGS)
@click.argument('n', type=int)
def compute_kaprekar(n):
    '''Given a four digit number with at least two distinct digits,
    this script computes the Kaprekar constant.
    '''
    check_valid(n)
    print(n, end='')
    while True:
        prev_n = n
        small = compute_sorted(n, reverse=False)
        large = compute_sorted(n, reverse=True)
        n = large - small
        if n != prev_n:
            print(f' -> {n}', end='')
        else:
            break
    print()


if __name__ == '__main__':
    compute_kaprekar()
