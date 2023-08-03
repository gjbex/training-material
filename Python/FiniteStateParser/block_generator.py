#!/usr/bin/env python
'''Module to generate block structureed random data.  When called as
   a script, it takes two options:
     -b <num> : number of blocks to generate
     -n <num> : number of data items per block
   output is written to stdout'''

import argparse
import random
import block


class BlockGenerator:
    '''Class that implements a block structured data generator'''

    def __init__(self, nr_blocks=1,
                 min_nr_items=2,
                 max_nr_items=4):
        '''Constructor that takes the number of blocks to be generared,
           and the minimum and maximum number of data items per block.
           These default to 1, 2, and 4 respectively.'''
        self._nr_blocks = nr_blocks
        self._min_nr_items = min_nr_items
        self._max_nr_items = max_nr_items
        self._nr_items = None
        self._curr_block = None
        self._curr_item = None
        self._reset()

    def _reset(self):
        '''resets internal state of the generator between calls to generate'''
        self._curr_block = 0
        self._curr_item = 0

    def __str__(self):
        return ('Block_generator at [{b_curr}, {i_curr}] of ' +
                '[{b_max}, {i_max}]').format(
            b_curr=self._curr_block, b_max=self._nr_blocks,
            i_curr=self._curr_item, i_max=self._nr_items)

    def get_nr_blocks(self):
        '''Return the number of blocks to be generated'''
        return self._nr_blocks

    def get_nr_items(self):
        '''Return the number of items to be generated per block'''
        return self._nr_items

    def _generate_value(self, data_block):
        '''Generate an item value.'''
        return str(random.random())

    def _create_block(self):
        '''Create a new Block object'''
        block_name = "block_{0}".format(self._curr_block)
        return block.Block(block_name)

    def generate(self):
        '''Generate the blocks'''
        self._reset()
        for self._curr_block in range(1, self._nr_blocks + 1):
            data_block = self._create_block()
            self._nr_items = random.randint(self._min_nr_items,
                                            self._max_nr_items)
            for self._curr_item in range(1, self._nr_items + 1):
                data_block.add_data(self._generate_value(data_block))
            yield data_block


class TypedBlockGenerator(BlockGenerator):
    '''Class that implements a typed block structured data generator'''

    def __init__(self, nr_blocks=1,
                 min_nr_items=2,
                 max_nr_items=4,
                 block_type=None):
        '''Constructor that takes the number of blocks to be generared,
           and the minimum and maximum number of data items per block.
           These default to 1, 2, and 4 respectively.'''
        BlockGenerator.__init__(self, nr_blocks, min_nr_items,
                                max_nr_items)
        self._block_type = block_type

    def _generate_value(self, data_block):
        '''Generate an item value.'''
        if data_block.get_type() == 'float':
            return random.random()
        elif data_block.get_type() == 'int':
            return random.randint(-1000, 1000)
        else:
            return ''.join(chr(random.randint(ord('A'), ord('Z'))) for _ in range(0, 5))

    def _create_block(self):
        '''Create a new Block object'''
        block_name = "block_{0}".format(self._curr_block)
        if self._block_type is None:
            block_type = random.choice(block.TypedBlock.types)
        else:
            block_type = self._block_type
        return block.TypedBlock(block_name, block_type)


def main():
    '''function called when the module is called as a script'''
    parser = argparse.ArgumentParser(
        description='generate block-structured data')
    parser.add_argument('--blocks', type=int, default=1,
                        action='store', dest='nr_blocks',
                        help='number of blocks to generate')
    parser.add_argument('--min', type=int, default=2,
                        action='store', dest='min_nr_items',
                        help='minimum number of items to generate')
    parser.add_argument('--max', type=int, default=4,
                        action='store', dest='max_nr_items',
                        help='maximum number of items to generate')
    parser.add_argument('--type', type=str, default=None,
                        action='store', dest='block_type',
                        help='type for the blocks, defaults to random')
    options = parser.parse_args()
    generator = TypedBlockGenerator(options.nr_blocks,
                                    options.min_nr_items,
                                    options.max_nr_items,
                                    options.block_type)
    for data_block in generator.generate():
        print(data_block)

if __name__ == '__main__':
    main()
