#!/usr/bin/env python

from argparse import ArgumentParser

def compute_end_address(base_address, info):
    var, base_size, size = info
    return base_address + base_size*size


def visualize_var(base_address, info, word_size, mask):
    lines = []
    var, base_size, size = info
    end_address = compute_end_address(base_address, info)
    for address in range(base_address, end_address, word_size):
        line = '0x{0:05x} {0:6d} 0b{0:12b}: {1:s}'.format(address & mask,
                                                          var)
        if address % 64 == 0:
            line += ' ################################'
        lines.append(line)
    return lines
        

def visualize_empty(end_address, base_address, word_size, mask):
    lines = []
    for address in range(end_address, base_address, word_size):
        line = '0x{0:05x} {0:6d} 0b{0:12b}: {1:s}'.format(address & mask,
                                                          '--')
        if address % 64 == 0:
            line += ' ################################'
        lines.append(line)
    return '\n'.join(lines)


if __name__ == '__main__':
    arg_parser = ArgumentParser(description='visualize memory dump')
    arg_parser.add_argument('file', help='memory dump file')
    arg_parser.add_argument('--word-size', type=int, default=4,
                            help='size of memory word')
    arg_parser.add_argument('--cache-line', type=int, default=16,
                            help='cache line size in words')
    arg_parser.add_argument('--mask', default='FFFF',
                            help='address mask')
    options = arg_parser.parse_args()
    stack_memory_map = dict()
    heap_memory_map = dict()
    with open(options.file) as dump_file:
        for line in dump_file:
            line = line.strip()
            data = line.split()
            if len(data) == 4:
                mem, var, address, base_size = data
                base_size = int(base_size)
                size = 1
            elif len(data) == 5:
                mem, var, address, base_size, size = data
            else:
                msg = "### error: line '" + line + "' is invalid"
                sys.stderr.write(msg)
            if mem == 'stack':
                stack_memory_map[address] = (var, int(base_size), int(size))
            else:
                heap_memory_map[address] = (var, int(base_size), int(size))
    for memory_map in [stack_memory_map, heap_memory_map]:
        print('#' * 72)
        previous_end = 0
        for address_str in sorted(memory_map):
            base_address = int(address_str, 16)
            if previous_end > 0 and previous_end != base_address:
                mem_str = visualize_empty(previous_end, base_address,
                                          options.word_size,
                                          int(options.mask, 16))
                print(mem_str)
            mem_strs = visualize_var(base_address,
                                     memory_map[address_str],
                                     options.word_size,
                                     int(options.mask, 16))
            for mem_str in mem_strs:
                print(mem_str)
            previous_end = compute_end_address(base_address,
                                           memory_map[address_str])
