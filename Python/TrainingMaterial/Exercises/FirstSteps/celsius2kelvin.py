#!/usr/bin/env python

import sys

def celsius2kelvin(temp):
    return temp + 273.15

def kelvin2celsius(temp):
    return temp - 273.15

if __name__ == '__main__':
    temp = float(sys.argv[1])
    print celsius2kelvin(temp)
