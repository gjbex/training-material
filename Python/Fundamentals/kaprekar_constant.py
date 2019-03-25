#!/usr/bin/env python

import click

CONTEXT_SETTINGS = {
        'help_option_names': ('-h', '--help')
}


def compute_sorted(n, reverse=True):
    return int(''.join(sorted(str(n), reverse=reverse)))


@click.command(context_settings=CONTEXT_SETTINGS)
@click.argument('n', type=int, default=1112)
def compute_kaprekar(n):
    print(n, end='')
    small = compute_sorted(n, reverse=False)
    prev_small = 0
    while True:
        large = compute_sorted(n, reverse=True)
        n = large - small
        prev_small = small
        small = compute_sorted(n, reverse=False)
        if small != prev_small:
            print(' ->', n, end='')
        else:
            break
    print()


if __name__ == '__main__':
    compute_kaprekar()
