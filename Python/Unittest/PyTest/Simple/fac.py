#!/usr/bin/env python

def bad_fac(n):
    return 1 if n < 2 else n*fac(n - 1)


def fac(n):
    if n in [0, 1]:
        return 1;
    elif n >= 2:
        result = 1
        for i in range(2, n + 1):
            result *= i;
        return result
    else:
        raise ValueError('fac argument must be positive')

if __name__ == '__main__':
    from argparse import ArgumentParser
    arg_parser = ArgumentParser(description='compute factorials')
    arg_parser.add_argument('n', type=int, default=5,
                            help='maximum argument')
    options = arg_parser.parse_args()
    for i in range(options.n + 1):
        print(f'fac({i}) = {fac(i)}')
