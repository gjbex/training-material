'''Auxilary classes for exceptions.  Can be called directly with a file
   name as argument'''


class ParseError(Exception):
    '''base exception class for parse errors'''
    def __init__(self, parser):
        Exception.__init__(self)
        self._parser = parser

    def get_parser_state(self):
        '''return the state of the parser when the exception wsa thrown'''
        return self._parser.get_state()

    def get_line_nr(self):
        '''returns the line number which was being parsed when the
           exception was raised'''
        return self._parser.get_line_nr()


class NestedBlocksError(ParseError):
    '''exception that indicates that a begin block was found within a
       block'''
    def __init__(self, parser):
        ParseError.__init__(self, parser)
        self._current_block_name = parser._current_block.get_name()
        self._nested_block_name = parser._match.group(1)

    def __str__(self):
        return ("line {0}: block {1} seems to be nested "
                "within block {2}".format(self.get_line_nr(),
                                          self._current_block_name,
                                          self._nested_block_name))


class NonMatchingBlockDelimitersError(ParseError):
    '''exception that indicates that a begin block is closed with a
       non-matching end block'''
    def __init__(self, parser):
        ParseError.__init__(self, parser)
        self._current_block_name = parser._current_block.get_name()
        self._end_block_name = parser._match.group(1)

    def __str__(self):
        return "line {0}: block {1} is closed b block {2}".format(
            self.get_line_nr(), self._current_block_name,
            self._end_block_name)


class DanglingEndBlockError(ParseError):
    '''exception that indicates that an end block is encountered with a
       begin block'''
    def __init__(self, parser):
        ParseError.__init__(self, parser)
        self._end_block_name = parser._match.group(1)

    def __str__(self):
        return ('line {0}: block {1} is closed without '
                'previous begin block'.format(self.get_line_nr(),
                                              self._end_block_name))


class NonClosedBlockError(ParseError):
    '''exception that indicates the file ends without closing the
       last block'''
    def __init__(self, parser):
        ParseError.__init__(self, parser)
        self._begin_block_name = parser._current_block.get_name()

    def __str__(self):
        return 'line {0}: block {1} is not closed'.format(
            self.get_line_nr(), self._begin_block_name)


class UnknownStateError(Exception):
    '''indicates that the parser has reached an unknown state'''
    def __init__(self, state):
        Exception.__init__(self)
        self._state = state

    def __str__(self):
        return "parser has reached unknown state '{0}'".format(self._state)
