#!/usr/bin/env python

from argparse import ArgumentParser
from xml.dom.minidom import Document


def main():
    arg_parser = ArgumentParser('creates XML encoded block data')
    arg_parser.add_argument('--blocks', type=int, default=3,
                            dest='nr_blocks', help='number blocks to make')
    arg_parser.add_argument('--items', type=int, default=2,
                            dest='nr_items', help='number items to make')
    options = arg_parser.parse_args()
    doc = Document()
    blocks = doc.createElement('blocks')
    doc.appendChild(blocks)
    for block_nr in range(1, options.nr_blocks + 1):
        block = doc.createElement('block')
        block.setAttribute('name', 'block_{0:02d}'.format(block_nr))
        blocks.appendChild(block)
        for item_nr in range(0, options.nr_items):
            item = doc.createElement('item')
            text = doc.createTextNode('{0}.{1}'.format(item_nr, block_nr))
            item.appendChild(text)
            block.appendChild(item)
    print(doc.toprettyxml(indent='  '))

if __name__ == '__main__':
    main()
