#!/usr/bin/env python


import click
import sys

CONTEXT_SETTINGS = {
    'help_option_names': ('-h', '--help'),
}


def compute_digit_prod(n):
    prod = 1
    for digit_str in str(n):
        prod *= int(digit_str)
    return prod


def compute_persistance(n):
    numbers = [n]
    while len(str(n)) > 1:
        n = compute_digit_prod(n)
        numbers.append(n)
    return numbers


@click.command(context_settings=CONTEXT_SETTINGS)
@click.argument('n', type=int)
@click.option('--verbose', '-v', is_flag=True, help='verbose output')
def main(n, verbose):
    '''Compute the persistance of N, i.e., the number of times that the digits
    of a number can be multiplied until it consists of a single digits.
    '''
    if n < 0:
        print('Error: n should be positive', file=sys.stderr)
        sys.exit(1)
    numbers = compute_persistance(n)
    if  verbose:
        print(' -> '.join(str(number) for number in numbers))
    print(len(numbers))


if __name__ == '__main__':
    main()
