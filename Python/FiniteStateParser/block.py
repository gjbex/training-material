#!/usr/bin/env python
'''module that defines the Block class'''

class Block():
    '''Class representing a data block, a block has a name, a description,
       a data type, and its data'''

    def __init__(self, name):
        '''constructor, takes the block's name as an argument'''
        self._name = name
        self._data = []

    def _repr_haeder(self):
        '''return header for __repr__'''
        return 'block {0}:'.format(self.get_name())
        
    def __repr__(self):
        '''create a string representation of the block'''
        header = self._repr_haeder()
        data = '\n\t'.join([str(item) for item in self._data])
        return '{0}\n\t{1}'.format(header, data)

    def _str_header(self):
        '''return header for __str__'''
        return 'begin {0}'.format(self.get_name())

    def __str__(self):
        '''create a string of the block'''
        header = self._str_header()
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


class TypedBlock(Block):
    '''Block data is of a single, specified type'''

    types = ['str', 'int', 'float']
    default_type = 'str'

    def __init__(self, name, block_type=None):
        '''constructor, takes the block's name and type, the latter
           defaults to 'str'.'''
        Block.__init__(self, name)
        if block_type is None:
            block_type = TypedBlock.default_type
        if block_type in TypedBlock.types:
            self._type = block_type
        else:
            raise UnknownBlockTypeError(block_type)

    def get_type(self):
        '''return the block's type'''
        return self._type

    def _repr_haeder(self):
        return 'block {0}[{1}]:'.format(
            self.get_name(), self.get_type())
        
    def _str_header(self):
        return 'begin {0}[{1}]'.format(
            self.get_name(), self.get_type())

    def add_data(self, data):
        '''given a data item, add it to the block's data'''
        if self.get_type() == 'int':
            data = int(data)
        elif self.get_type() == 'float':
            data = float(data)
        Block.add_data(self, data)


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


class UnknownBlockTypeError(Exception):
    '''indicates that the type for the block is unimplemented'''
    def __init__(self, block_type):
        Exception.__init__(self)
        self._type = block_type

    def __str__(self):
        return 'unknown block type "{0}"'.format( self._type)


class TypedBlockTest(unittest.TestCase):
    '''Tests for the typed block class'''

    def test_typed_constructor(self):
        '''create an TypedBlock object, tests its name and type'''
        name = 'test name'
        block_type = 'int'
        block = TypedBlock(name, block_type)
        self.assertIsNotNone(block)
        self.assertEquals(block.get_name(), name)
        self.assertEquals(block.get_type(), block_type)

    def test_typed_constructor_default(self):
        '''create a default typed TypedBlock object, tests its name and type'''
        name = 'test name'
        block_type = 'str'
        block = TypedBlock(name)
        self.assertIsNotNone(block)
        self.assertEquals(block.get_name(), name)
        self.assertEquals(block.get_type(), block_type)

    def test_typed_constructor_none(self):
        '''create a None typed TypedBlock object, tests its name and type'''
        name = 'test name'
        block_type = 'str'
        block = TypedBlock(name, None)
        self.assertIsNotNone(block)
        self.assertEquals(block.get_name(), name)
        self.assertEquals(block.get_type(), block_type)

    def test_typed_repr(self):
        '''create a TypedBlock object, add some data, check its
           representation'''
        name = 'test_name'
        block_type = 'str'
        data = ['gamma', 'alpha', 'beta']
        data_repr = '\n\t'.join([str(item) for item in data])
        target = 'block {0}[{1}]:\n\t{2}'.format(name, block_type, data_repr)
        block = TypedBlock(name, block_type)
        for item in data:
            block.add_data(item)
        self.assertEquals(repr(block), target)

    def test_typed_str(self):
        '''create a TypedBlock object, add some data, check its
           string representation'''
        name = 'test_name'
        block_type = 'str'
        data = ['gamma', 'alpha', 'beta']
        data_repr = '\n\t'.join([str(item) for item in data])
        target = 'begin {0}[{1}]\n\t{2}\nend {0}'.format(name, block_type,
                                                         data_repr)
        block = TypedBlock(name, block_type)
        for item in data:
            block.add_data(item)
        self.assertEquals(str(block), target)

    def test_typed_str_data_ordered(self):
        '''create a TypedBlock object, add some str data, check whether the
           data is ordered upon return'''
        name = 'test_name'
        block_type = 'str'
        data = ['gamma', 'alpha', 'beta']
        block = TypedBlock(name, block_type)
        for item in data:
            block.add_data(item)
        block.sort_data()
        self.assertEquals(block.get_data(), sorted(data))

    def test_typed_int_data_ordered(self):
        '''create a TypedBlock object, add some int data, check whether the
           data is ordered upon return'''
        name = 'test_name'
        block_type = 'int'
        data = [17, 2, -1, 8]
        block = TypedBlock(name, block_type)
        for item in data:
            block.add_data(item)
        block.sort_data()
        self.assertEquals(block.get_data(), sorted(data))

    def test_typed_float_data_ordered(self):
        '''create a TypedBlock object, add some fload data,
           check whether the data is ordered upon return'''
        name = 'test_name'
        block_type = 'float'
        data = [17.3, 2.0e-4, -1, -8.13]
        block = TypedBlock(name, block_type)
        for item in data:
            block.add_data(item)
        block.sort_data()
        self.assertEquals(block.get_data(), sorted(data))

    def test_typed_unknown_type_error(self):
        '''create a TypedBlock of a non-existing type, check
           for exception'''
        name = 'block_name'
        block_type = 'bla'
        with self.assertRaises(UnknownBlockTypeError):
            block = TypedBlock(name, block_type)

    def test_wrong_type_error(self):
        '''create a TypeBlock, and add wrong type of data'''
        name = 'test_name'
        block_type = 'int'
        data = 'alpha'
        block = TypedBlock(name, block_type)
        with self.assertRaises(ValueError):
            block.add_data(data)


if __name__ == '__main__':
    unittest.main()

