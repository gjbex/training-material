#!/usr/bin/env python

from argparse import ArgumentParser, FileType
import logging
import sys
import xml.sax
from xml.sax.handler import ContentHandler


class Block(object):

    def __init__(self, name):
        self._name = name
        self._data = []

    @property
    def name(self):
        return self._name

    def add_data(self, value):
        self._data.append(value)

    def finish(self):
        self._data.sort()

    def __str__(self):
        return '\n'.join(['{0}: {1}'.format(self.name, x)
                          for x in self._data])


class BlocksHandler(ContentHandler):

    def __init__(self):
        self._blocks = None
        self._stack = None
        self._in_item = None

    @property
    def in_item(self):
        return self._in_item

    @in_item.setter
    def in_item(self, value):
        self._in_item = value

    def get_blocks(self):
        return self._blocks

    def startDocument(self):
        logging.info('start of document')
        self._blocks = []
        self._stack = []
        self.in_item = False

    def startElement(self, name, attrs):
        if name == 'block':
            logging.info('start of {0}'.format(attrs.getValue('name')))
            parent_name = ''
            if self._stack:
                parent_name = self._stack[-1].name + '/'
            block = Block(parent_name + attrs.getValue('name'))
            self._stack.append(block)
        elif name == 'item':
            self.in_item = True

    def characters(self, contents):
        if self.in_item:
            contents = contents.strip()
            if contents:
                data = float(contents.strip())
                logging.info("found '{0}'".format(data))
                self._stack[-1].add_data(data)

    def endElement(self, name):
        if name == 'block':
            block = self._stack.pop()
            block.finish()
            self._blocks.append(block)
            logging.info('end of {0}'.format(block.name))
        elif name == 'item':
            self.in_item = False

    def endDocument(self):
        logging.info('end of document')


def main():
    arg_parser = ArgumentParser(description='reformat XML code')
    arg_parser.add_argument('-verbose', action='store_true',
                            help='print verbose output')
    arg_parser.add_argument('file', type=FileType('r'),
                            help='XML file to convert')
    options = arg_parser.parse_args()
    if options.verbose:
        logging.basicConfig(level=logging.INFO)
    handler = BlocksHandler()
    xml.sax.parse(options.file, handler)
    print('\n'.join(str(b) for b in handler.get_blocks()))

if __name__ == '__main__':
    status = main()
    sys.exit(status)
