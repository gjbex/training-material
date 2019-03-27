#!/usr/bin/env python

import click
from collections import Counter
from concurrent.futures import ProcessPoolExecutor
import mmap


def count_nucl(args):
    mem_map_name, start, size = args
    with open(mem_map_name, 'r+b') as mem_map_file:
        with mmap.mmap(mem_map_file.fileno(), 0,
                       access=mmap.ACCESS_READ) as mem_map:
            mem_map.seek(start)
            counter = Counter()
            for nucl in mem_map.read(size):
                counter[nucl] += 1
            return counter


def aggregate(results):
    counter = Counter()
    for result in results:
        for nucl, count in result.items():
            counter[nucl] += count
    return counter


def compute(mem_map_name, chunk_size=2**16, max_workers=4):
    with open(mem_map_name, 'r+b') as mem_map_file:
        with mmap.mmap(mem_map_file.fileno(), 0,
                       access=mmap.ACCESS_READ) as mem_map:
            nr_chunks = mem_map.size()//chunk_size
    args = [(mem_map_name, i*chunk_size, chunk_size)
                for i in range(nr_chunks)]
    with ProcessPoolExecutor(max_workers=max_workers) as executor:
        results = executor.map(count_nucl, args)
    return aggregate(results)


CONTEXT_SETTINGS = {
    'help_option_names': ('-h', '--help'),
}

@click.command(context_settings=CONTEXT_SETTINGS)
@click.argument('file')
@click.option('--chunk-size', '-c', type=int, default=2**16,
              help='chunk size for computation')
@click.option('--max-workers', '-m', type=int, default=4,
              help='maximum number of workers for computation')
def main(file, chunk_size, max_workers):
    '''Count the number of nucleotides in the given FILE
    '''
    results = compute(file, chunk_size, max_workers)
    total = 0
    for nucl, count in results.items():
        total += count
        print(f'{nucl}: {count}')
    print(f'total = {total}')


if __name__ == '__main__':
    main()
