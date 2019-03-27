#!/usr/bin/env python

import click
from collections import Counter
from concurrent.futures import ProcessPoolExecutor
import mmap

def count_nucl(mem_map, start, size):
    mem_map.seek(start)
    counter = Counter()
    for nucl in mem_map.read(size):
        counter[nucl] += 1
    return counter


def aggregate(results):
    counter = Counter()
    for result in results:
        counter += result
    return counter


def compute(mem_map, chunk_size=2**16, max_workers=4):
    nr_chunks = mem_map.size()//chunk_size
    args = [(mem_map, i*chunk_size) for i in range(nr_chunks)]
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
    with open(file, 'r+b') as nucl_file:
        with mmap.mmap(nucl_file.fileno(), 0) as mem_map:
            results = compute(mem_map, chunk_size, max_workers)
            for nucl, count in results:
                print(f'{nucl}: {count}')

if __name__ == '__main__':
    main()
