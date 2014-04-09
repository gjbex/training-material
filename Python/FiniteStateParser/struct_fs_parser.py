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

# last_match will hold the match object that is produced in the test
# functions to be used in the rest of the parser
last_match = None
# compile the regular expressions to be used for performance reasons
comment_pattern = re.compile(r"\s*#.*")
block_begin_pattern = re.compile(r"\s*begin\s+(\w+)")
block_end_pattern = re.compile(r"\s*end\s+(\w+)")
# current_block holds the name of the block that is being parsed, its
# value is None when outside a block, note that it doubles as state
# variable
current_block = None
# dictionary to hold the blocks' content
block_content = {}

def parse(file_name):
    """function that takes a file name, and returns a dictionary of blocks,
    the keys are the names of the blocks, the values are lists of their
    content"""
    global current_block, block_content

    def filter_line(line):
        global comment_pattern
        return comment_pattern.sub("", line.strip())

    def is_blank(line):
        return len(line) == 0

    def is_block_begin(line):
        global last_match, block_begin_pattern
        last_match = block_begin_pattern.match(line)
        return last_match is not None

    def is_block_end(line):
        global last_match, block_end_pattern
        last_match = block_end_pattern.match(line)
        return last_match is not None

    def is_in_block():
        global current_block
        return current_block is not None

    def set_current_block():
        global current_block, block_content
        current_block = last_match.group(1)
        block_content[current_block] = []

    def check_is_not_in_block():
        global current_block, last_match
        if is_in_block():
            msg = "block {0} is not close when opening {1}".format(
                current_block, last_match.group(1))
            raise ParseError(msg)

    def check_end_matches_begin():
        global current_block, last_match
        if last_match.group(1) != current_block:
            msg = "block %s is closed with %s" % \
               (last_match.group(1), current_block)
            raise ParseError(msg)

    def store_data(line):
        global block_content, current_block
        block_content[current_block].append(line)

    def sort_block_data():
        global block_content
        for key in block_content.keys():
            block_content[key].sort()

# open file, specified on command line
    block_file = open(file_name, 'r')

# iterate over the lines in the file and process
    for line in block_file:
        line = filter_line(line)
        if not is_blank(line):
            if is_block_begin(line):
                check_is_not_in_block()
                set_current_block()
            elif is_block_end(line):
                check_end_matches_begin()
                current_block = None
            elif is_in_block():
                store_data(line)

# close the file
    block_file.close()

    sort_block_data()

    return block_content

def main():
    """main program to be executed when this module is used as a script"""
    import sys
# check whether at least one command line argument has been passed
    if len(sys.argv) == 1:
        print "### error: no file specified"
        exit(1)
    content = parse(sys.argv[1])
    for block_name in content.keys():
        for value in content[block_name]:
            print "%s: '%s'" % (block_name, value)

if __name__ == "__main__":
    main()

