#!/usr/bin/env python
'''script for temperature conversion, can be used to as a module to load
conversion functions from'''

from argparse import ArgumentParser
import sys

def celsius2kelvin(temp):
    '''convert given temperature from degree Celsius to Kelvin'''
    return temp + 273.15

def kelvin2celsius(temp):
    '''convert given temperature from Kelvin to degree Celsius'''
    return temp - 273.15

if __name__ == '__main__':
    arg_parser = ArgumentParser(description='Temperature converter')
    arg_parser.add_argument('-c2k', action='store_true',
                            help='convert from degree Celsius to Kelvin')
    arg_parser.add_argument('-k2c', action='store_true',
                            help='convert Kelvin to degree Celsius')
    arg_parser.add_argument('temp', type=float, help='temperature')
    options = arg_parser.parse_args()
    if options.c2k:
        print celsius2kelvin(options.temp)
    else:
        print kelvin2celsius(options.temp)
