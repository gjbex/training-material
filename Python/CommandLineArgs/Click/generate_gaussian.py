#!/usr/bin/env python

import random
import click


CONTEXT_SETTINGS = {
    'help_option_names': ('-h', '--help')
}


@click.command(context_settings=CONTEXT_SETTINGS)
@click.argument('n', type=int, default=1)
@click.option('--mu', '-m', type=float, default=0.0,
              help='mean value')
@click.option('--sigma', '-s', type=float, default=1.0,
              help='standard deviation')
@click.option('--index', '-i', is_flag=True,
              help='print index')
def generate_numbers(n, mu, sigma, index):
    '''This script generates N random values from a Gaussian
    distribution with mean value mu and standard deviation
    sigma.
    '''
    for i in range(n):
        if index:
            print(f'{i:d}\t', end='')
        number = random.gauss(mu, sigma)
        print(f'{number}')
    return 0

if __name__ == '__main__':
    generate_numbers()
