#!/usr/bin/env python
'''module that defines the Block class'''

class Block():
    '''Class representing a data block, a block has a name, a description,
       a data type, and its data'''

    def __init__(self, name):
        '''constructor, takes the block's name as an argument'''
        self._name = name
        self._data = []

    def __repr__(self):
        '''create a string representation of the block'''
        header = 'block {0}:'.format(self.get_name())
        data = '\n\t'.join([str(item) for item in self._data])
        return '{0}\n\t{1}'.format(header, data)

    def __str__(self):
        '''create a string of the block'''
        header = 'begin {0}'.format(self.get_name())
        data = '\n\t'.join([str(item) for item in self._data])
        footer = 'end {0}'.format(self.get_name())
        return '{0}\n\t{1}\n{2}'.format(header, data, footer)

    def get_name(self):
        '''returns the block's name'''
        return self._name

    def add_data(self, data):
        '''given a data item, add it to the block's data'''
        self._data.append(data)

    def sort_data(self):
        '''sort the block's data'''
        self._data.sort()

    def get_data(self):
        '''returns the data, sorted'''
        return self._data


# unit test implementation for Block class
import unittest

class BlockTest(unittest.TestCase):
    '''Tests for the block class'''

    def test_constructor(self):
        '''create an object, tests its name'''
        name = 'test name'
        block = Block(name)
        self.assertIsNotNone(block)
        self.assertEquals(block.get_name(), name)

    def test_repr(self):
        '''create a Block object, add some data, check its representation'''
        name = 'test_name'
        data = ['gamma', 'alpha', 'beta']
        data_repr = '\n\t'.join([str(item) for item in data])
        target = 'block {0}:\n\t{1}'.format(name, data_repr)
        block = Block(name)
        for item in data:
            block.add_data(item)
        self.assertEquals(repr(block), target)

    def test_str(self):
        '''create a Block object, add some data, check its representation'''
        name = 'test_name'
        data = ['gamma', 'alpha', 'beta']
        data_repr = '\n\t'.join([str(item) for item in data])
        target = 'begin {0}\n\t{1}\nend {0}'.format(name, data_repr)
        block = Block(name)
        for item in data:
            block.add_data(item)
        self.assertEquals(str(block), target)

    def test_data_ordered(self):
        '''create a Block object, add some data, check whether the data
           is ordered upon return'''
        name = 'test_name'
        data = ['gamma', 'alpha', 'beta']
        block = Block(name)
        for item in data:
            block.add_data(item)
        block.sort_data()
        self.assertEquals(block.get_data(), sorted(data))


if __name__ == '__main__':
    unittest.main()

