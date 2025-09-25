#!/usr/bin/env python
"""Parser for block-formatted data, blocks are named, and enclosed
in begin/end pairs, the script will print the sorted values in the block,
with the block's name prepended."""


import re
import sys

__version__ = "$Revision$"

# check whether at least one command line argument has been passed
if len(sys.argv) == 1:
    print("### error: no file specified")
    exit(1)

with open(sys.argv[1], 'r') as block_file:
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
        if match is not None:
                    # if current_block is not None, we are already in a block,
                    # raise error
            if current_block is not None:
                print(f"### error: block {current_block} is not close when opening {match[1]}")
                exit(2)
# now in a block, so change state
            current_block = match[1]
            block_content[current_block] = []
            continue
# check for end block
        match = block_end_pattern.match(line)
        if match is not None:
                    # if the end block name is not the current block, raise error
            if match[1] != current_block:
                print(f"### error: block {match[1]} is closed with {current_block}")
                exit(3)
# now out of a block, so change state
            current_block = None
            continue
# if not in a block, ignore the line
        if current_block is None:
            continue
# store block data
        block_content[current_block].append(line)

    # now print the data in the new format
    for key in list(block_content.keys()):
        block_content[key].sort()
        for value in block_content[key]:
            print(f"{key}: '{value}'")
