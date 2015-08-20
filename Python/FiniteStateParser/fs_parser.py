#!/usr/bin/env python
"""Module containing a parser for a simple block enocded data format"""

import re


class ParseError(Exception):
    """Exception thrown when a parse error occurs"""

    def __init__(self, msg):
        Exception.__init__(self)
        self.msg = msg

    def __str__(self):
        return repr(self.msg)


def parse(file_name):
    """function that takes a file name, and returns a dictionary of blocks,
    the keys are the names of the blocks, the values are lists of their
    content"""
# open file, specified on command line
    block_file = open(file_name, 'r')
# compile the regular expressions to be used for performance reasons
    comment_pattern = re.compile(r"\s*#.*")
    block_start_pattern = re.compile(r"\s*begin\s+(\w+)")
    block_end_pattern = re.compile(r"\s*end\s+(\w+)")
# current_block holds the name of the block that is being parsed, its
# value is None when outside a block, note that it doubles as state
# variable
    current_block = None
# dictionary to hold the blocks' content
    block_content = {}
    for line in block_file:
        # remove leading/triailing spaces, and comments (i.e., everything
        # following a '#'
        line = comment_pattern.sub("", line.strip())
        # ignore blank lines
        if len(line) == 0:
            continue
        # check for begin block
        match = block_start_pattern.match(line)
        if match:
            # if current_block is not None, we are already in a block,
            # raise error
            if current_block:
                msg = "block %s is not close when opening %s" % \
                    (current_block, match.group(1))
                raise ParseError(msg)
# now in a block, so change state
            current_block = match.group(1)
            block_content[current_block] = []
            continue
# check for end block
        match = block_end_pattern.match(line)
        if match:
            # if the end block name is not the current block, raise error
            if match.group(1) != current_block:
                msg = "block %s is closed with %s" % \
                   (match.group(1), current_block)
                raise ParseError(msg)
# now out of a block, so change stateatch.group(1), current_block)
            current_block = None
            continue
# if not in a block, ignore the line
        if current_block is None:
            continue
        else:
            # store block data
            block_content[current_block].append(line)
# close the file
    block_file.close()
# now sort the data
    for key in list(block_content.keys()):
        block_content[key].sort()
    return block_content


def main():
    """main program to be executed when this module is used as a script"""
    import sys
# check whether at least one command line argument has been passed
    if len(sys.argv) == 1:
        print("### error: no file specified")
        exit(1)
    content = parse(sys.argv[1])
    for block_name in content:
        for value in content[block_name]:
            print("%s: '%s'" % (block_name, value))

if __name__ == "__main__":
    main()
