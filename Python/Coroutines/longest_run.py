#!/usr/bin/env python

from collections import defaultdict


def longest_run():
    runs = defaultdict(lambda: 0)
    buffer = None
    while True:
        data = yield runs
        if data:
            if not buffer:
                prev = data.pop(0)
                buffer = [prev]
                run_length = 1
            else:
                prev = buffer[-1]
                if prev != data[0]:
                    run_length = len(buffer)
                    if run_length > runs[prev]:
                        runs[prev] = run_length
                    prev = data.pop(0)
                    buffer = [prev]
                    run_length = 1
                else:
                    buffer.append(prev)
            while data:
                current = data.pop(0)
                if current == prev:
                    run_length += 1
                    buffer.append(current)
                else:
                    if run_length > runs[prev]:
                        runs[prev] = run_length
                    prev = current
                    buffer = [prev]
                    run_length = 1
    return runs


def print_run_lengths(runs, prefix=''):
    for char, run_length in runs.items():
        print(f'{prefix}{char}: {run_length}')

if __name__ == '__main__':
    data_stream = [
        'aabbbba',
        'aaaabb',
        'bbbbbaa',
    ]
    longest_runner = longest_run()
    next(longest_runner)
    for block_nr, data in enumerate(data_stream):
        print(data)
        runs = longest_runner.send(list(data))
        print(f'  result for block {block_nr + 1}')
        print_run_lengths(runs, '    ')
    longest_runner.close()
