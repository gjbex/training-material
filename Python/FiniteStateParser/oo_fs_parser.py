#!/usr/bin/env python
'''Module containing a parser for a simple block enocded data format'''

import re


class ParseError(Exception):
    '''Exception thrown when a parse error occurs'''

    def __init__(self, msg):
        '''constructor taking a message'''
        Exception.__init__(self)
        self.msg = msg

    def __str__(self):
        '''exception's string representation'''
        return repr(self.msg)


def parse(file_name):
    '''function that takes a file name, and returns a list of blocks,
       instances of class Block.'''
    from block import Block
# open file, specified on command line
    block_file = open(file_name, 'r')
# compile the regular expressions to be used for performance reasons
    comment_pattern = re.compile(r'\s*#.*')
    block_start_pattern = re.compile(r'\s*begin\s+(\w+)')
    block_end_pattern = re.compile(r'\s*end\s+(\w+)')
# current_block holds an instance of Block for the block that is being
# parsed, its # value is None when outside a block, note that it doubles
# as state variable
    current_block = None
# list to hold the blocks
    blocks = []
    for line in block_file:
        # remove leading/triailing spaces, and comments (i.e., everything
        # following a '#'
        line = comment_pattern.sub('', line.strip())
# ignore blank lines
        if len(line) == 0:
            continue
# check for begin block
        match = block_start_pattern.match(line)
        if match is not None:
            # if current_block is not None, we are already in a block,
            # raise error
            if current_block is not None:
                raise ParseError(
                    'block {0} is not close when opening {1}'.format(
                        current_block.get_name(), match.group(1)))
# now in a block, so change state
            current_block = Block(match.group(1))
            continue
# check for end block
        match = block_end_pattern.match(line)
        if match is not None:
            # if the end block name is not the current block, raise error
            if match.group(1) != current_block.get_name():
                raise ParseError(
                    'block {0} is closed with {1}'.format(
                        match.group(1), current_block.get_name()))
# now out of a block, add current block to the list, and change state
            blocks.append(current_block)
            current_block = None
            continue
# if not in a block, ignore the line
        if current_block is None:
            continue
        else:
            # store block data
            current_block.add_data(line)
# close the file
    block_file.close()
    return blocks


def main():
    '''function to be executed when this module is used as an executable'''
    import sys
# check whether at least one command line argument has been passed
    if len(sys.argv) == 1:
        print('### error: no file specified')
        exit(1)
    blocks = parse(sys.argv[1])
    for block in blocks:
        for value in block.get_data():
            print('{0}: "{1}""'.format(block.get_name(), value))

if __name__ == '__main__':
    main()
