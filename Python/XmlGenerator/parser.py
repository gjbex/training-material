#!/usr/bin/env python

import re, sys

from states import State

class Parser(object):

    def __init__(self):
        self._states = set('doc_start', 'start')
        self._events = []
        self._buffer = ''


        
def main():
    print State.state_names()
    d = State.get_state('Doc_start')
    print d.name
    d = State.get_state('bla')
    print d
    return 0

if __name__ == '__main__':
    status = main()
    sys.exit(status)

