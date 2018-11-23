#!/usr/bin/env python

from argparse import ArgumentParser
import os
import platform
import sys

if __name__ == '__main__':
    arg_parser = ArgumentParser(description='system and process info utility')
    arg_parser.add_argument('--platform', action='store_true',
                            help='show platform info')
    arg_parser.add_argument('--python', action='store_true',
                            help='show Python related info')
    arg_parser.add_argument('--numerics', action='store_true',
                            help='show Python numerics info')
    arg_parser.add_argument('--env', action='store_true',
                            help='show environment info')
    options = arg_parser.parse_args()
    if options.platform:
        print(f'machine: {platform.machine()}')
        print(f'node: {platform.node()}')
        print(f'system: {platform.system()}')
        print(f'release: {platform.release()}')
        print(f'version: {platform.version()}')
        print(f'processor: {platform.processor()}')
        print(f'byte order: {sys.byteorder}')
        if platform.system() == 'Linux':
            print(f'distribution: {platform.linux_distribution()[0]}')
            print(f'libc version: {platform.libc_ver()[1]}')
            print(f'nr. CPUs: {os.cpu_count()}')
            print(f'nr. usable CPUs: {len(os.sched_getaffinity(0))}')
            load_avg = ", ".join(f'{x:.2f}' for x in os.getloadavg())
            print(f'load avg.: {load_avg}')
    if options.python:
        version = '{0:d}.{1:d}.{2:d}'.format(sys.version_info.major,
                                             sys.version_info.minor,
                                             sys.version_info.micro)
        print(f'version: {version}')
        print(f'installed in: {sys.base_exec_prefix}')
        print(f'executable: {sys.executable}')
        print(f'allocated blocks: {sys.getallocatedblocks():d}')
        print('loaded modules:\n    ', end='')
        print('\n    '.join(sorted(sys.modules.keys())))
    if options.numerics:
        print(f'float max: {sys.float_info.max}')
        print(f'float min: {sys.float_info.min}')
        print(f'float epsilon: {sys.float_info.epsilon}')
        print(f'float digists: {sys.float_info.digits}')
    if options.env:
        print(f'user: {os.getenv("USER")}')
        print(f'home directory: {os.getenv("HOME")}')
        print(f'nr. OpenMP threads: {os.getenv("OMP_NUM_THREADS","1")}')
