#!/usr/bin/env python
'''parser for block-structured data using the pyparsing module'''

from pyparsing import (alphas, alphanums, restOfLine,
                       Literal, Keyword, Word, CharsNotIn, Group, Combine,
                       Optional, ZeroOrMore, OneOrMore,
                       LineStart, LineEnd, NotAny,
                       ParserElement, ParseFatalException)
from block import Block

ParserElement.setDefaultWhitespaceChars(' \t')

current_block = None
blocks = []


def create_block(token):
    global current_block
    current_block = Block(token[0])


def finish_block(parsed_str, location, token):
    global current_block, blocks
    if token[0] == current_block.get_name():
        blocks.append(current_block)
        current_block = None
    else:
        message = 'mismatched begin {0}/end {1}'
        block_name = current_block.get_name()
        raise ParseFatalException(parsed_str, loc=location,
                                  msg=message.format(block_name, token[0]))


def handle_data(token):
    global current_block
    current_block.add_data(token[0])

eol = LineEnd().suppress()
begin = Keyword('begin').suppress()
end = Keyword('end').suppress()
comment = (Literal('#') + restOfLine).suppress()
data_value = Combine(OneOrMore(CharsNotIn('#\n\r')))
data = LineStart() + Optional(data_value) + Optional(comment) + eol
block_name = Word(alphas, alphanums + '_')
begin_block = LineStart() + begin + block_name + Optional(comment) + eol
end_block = LineStart() + end + block_name + Optional(comment) + eol
junk = ZeroOrMore(LineStart() + NotAny(begin) + restOfLine + eol).suppress()
block_def = begin_block + Group(ZeroOrMore(NotAny(end) + data)) + end_block
block_defs = junk + OneOrMore(block_def + junk)

begin_block.addParseAction(create_block)
end_block.addParseAction(finish_block)
data_value.addParseAction(handle_data)

test_str = '''
bla bla
begin block_1 # bla bla
    0.17  # suspicious value
# comment line
   -7.34
end block_1
# and noe the second block
begin block_2
    17.34
    11.8
end block_2

'''

results = block_defs.parseString(test_str)

for data_block in blocks:
    print(data_block)
