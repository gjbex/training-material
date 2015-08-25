#!/usr/bin/env python
'''parser for block-structured data using the pyparsing module'''

from pyparsing import (alphas, alphanums, restOfLine,
                       Literal, Keyword, Word, CharsNotIn, Group,
                       Combine, Optional, ZeroOrMore, OneOrMore,
                       LineStart, LineEnd, NotAny, White,
                       ParserElement, ParseFatalException)
import unittest
from block import Block

ParserElement.setDefaultWhitespaceChars(' \t')


class BlockPyParser:
    '''pyparsing based parser class for block-structured data'''

    def __init__(self):
        '''Constructor'''
        self._current_block = None
        self._blocks = []
        self._define_grammar()

    def _create_block(self, toks):
        self._current_block = Block(toks[0])

    def _finish_block(self, parsed_str, location, toks):
        if toks[0] == self._current_block.get_name():
            self._blocks.append(self._current_block)
            self._current_block = None
        else:
            message = 'mismatched begin {0}/end {1}'.format(
                self._current_block.get_name(), toks[0])
            raise ParseFatalException(parsed_str, loc=location, msg=message)

    def _handle_data(self, toks):
        self._current_block.add_data(toks[0].strip())

    def _define_actions(self):
        '''Internal method to define the various parse actions by currying
           with parser object.  To be called from grammar initializing
           method'''
        self._begin_block_action = lambda toks: self._create_block(toks)
        self._end_block_action = lambda s, l, t: self._finish_block(s, l, t)
        self._data_value_action = lambda toks: self._handle_data(toks)

    def _define_grammar(self):
        '''define the grammar to be used, and add actions'''
        self._define_actions()
        eol = LineEnd().suppress()
        white = Optional(White()).suppress()
        begin = Keyword('begin').suppress()
        end = Keyword('end').suppress()
        comment = (Literal('#') + restOfLine).suppress()
        data_value = Combine(OneOrMore(CharsNotIn('#\n\r')))
        data_line = (LineStart() + white + Optional(data_value) +
                     Optional(comment) + eol)
        block_name = Word(alphas, alphanums + '_')
        begin_block = (LineStart() + begin + block_name +
                       Optional(comment) + eol)
        end_block = LineStart() + end + block_name + Optional(comment) + eol
        junk = ZeroOrMore(LineStart() + white + NotAny(begin) +
                          restOfLine + eol).suppress()
        data = Group(ZeroOrMore(NotAny(end) + data_line))
        block_def = begin_block + data + end_block
        block_defs = junk + OneOrMore(block_def + junk)
        self._grammar = block_defs
        begin_block.addParseAction(self._begin_block_action)
        end_block.addParseAction(self._end_block_action)
        data_value.addParseAction(self._data_value_action)

    def parse(self, block_str):
        '''parse the given string'''
        return self._grammar.parseString(block_str)

    def get_blocks(self):
        '''return the blocks that were parsed'''
        return self._blocks


class BlockPyParserTest(unittest.TestCase):

    def test_two_blocks(self):
        test_str = '''
    bla bla
begin block_1 # bla bla
            0.17  # suspicious value
# comment line
           -7.34
           18.9
end block_1
# and noe the second block
begin block_2
            17.34
            11.8
end block_2

        '''
        parser = BlockPyParser()
        results = parser.parse(test_str)
        blocks = parser.get_blocks()
        self.assertEqual(len(blocks), 2)
        self.assertEqual(blocks[0].get_data(), ['0.17', '-7.34', '18.9'])
        self.assertEqual(blocks[1].get_data(), ['17.34', '11.8'])


if __name__ == '__main__':
    unittest.main()
