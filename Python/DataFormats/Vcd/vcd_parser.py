#!/usr/bin/env python

from argparse import ArgumentParser
import sys

class VcdParseError(Exception):
    pass

def demangle_name(name):
    return name.split('->').pop().replace('@', '_')

def parse_config_line(meta_data, line):
    if line.startswith('$var'):
        _, _, _, symbol, name, _ = line.split()
        meta_data[symbol] = demangle_name(name)

def parse_config(vcd_file):
    meta_data = dict()
    for line in vcd_file:
        line = line.strip()
        if line == '$end':
            break
        parse_config_line(meta_data, line)
    return meta_data
    
def store_buffer(data, buffer):
    if buffer:
        for var, value in buffer.items():
            data[var].append(value)

def update_buffer(buffer, line, meta_data):
    value, key = line.split()
    key = meta_data[key]
    if not value.startswith('b'):
        raise VcdParseException('incorrect value {0}'.format(value))
    value = int(value[1:], base=2) 
    buffer[key] = value

def init_data(meta_data):
    data = dict()
    data['time'] = list()
    for var in meta_data:
        data[meta_data[var]] = list()
    return data

def parse_data(vcd_file, meta_data):
    data = init_data(meta_data)
    time_stamp = None
    buffer = dict()
    for line in vcd_file:
        line = line.strip()
        if line.startswith('#'):
            if time_stamp is not None:
                store_buffer(data, buffer)
            time_stamp = int(line[1:])
            buffer['time'] = time_stamp
        elif line[0] in 'bBrR':
            update_buffer(buffer, line, meta_data)
    if time_stamp is not None:
        store_buffer(data, buffer)
    return data

def parse_vcd_file(vcd_file):
    meta_data = parse_config(vcd_file)
    return parse_data(vcd_file, meta_data)
                
def write_vcd_data_structure(out_file, data, sep=' '):
    columns = list(data.keys())
    out_file.write(sep.join(columns) + '\n')
    for time_step in range(len(data['time'])):
        data_line = list()
        for var in columns:
            data_line.append(data[var][time_step])
        out_file.write(sep.join(str(data_item) for data_item in data_line))
        out_file.write('\n')

if __name__ == '__main__':
    arg_parser = ArgumentParser(description='Parse a VCD file and dump '
                                            'data structure to file')
    arg_parser.add_argument('vcd_file', help='VCD file to parse')
    arg_parser.add_argument('-o', dest='out_file', help='output file')
    options = arg_parser.parse_args()
    with open(options.vcd_file, 'r') as vcd_file:
        data = parse_vcd_file(vcd_file)
    if options.out_file:
        with open(options.out_file, 'w') as out_file:
            write_vcd_data_structure(out_file, data)
    else:
        write_vcd_data_structure(sys.stdout, data)

