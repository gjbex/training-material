#!/usr/bin/env python

import sys

class BaseError(Exception):

    def __init__(self, position):
        super(BaseError, self).__init__()
        self._position = position

    @property
    def position(self):
        return self._position

    def __str__(self):
        return self.message


class MissingRBError(BaseError):

    def __init__(self, position):
        super(self.__class__, self).__init__(position)
        self.message = 'missing right bracket for bracket at {0}'.format(position)


class MissingLBError(BaseError):

    def __init__(self, position):
        super(self.__class__, self).__init__(position)
        self.message = 'missing left bracket for bracket at {0}'.format(position)


class TrailingCharsError(BaseError):

    def __init__(self, position):
        super(self.__class__, self).__init__(position)
        self.message = 'trailing characters at position {0}'.format(position)


def check_tree(tree):
    bracket_positions = []
    position = 1
    for character in tree:
        if character == '(':
            bracket_positions.append(position)
        elif character == ')':
            if bracket_positions:
                bracket_positions.pop()
            else:
                raise MissingLBError(position)
        if len(bracket_positions) == 0: break
        position += 1
    if len(bracket_positions) == 0 and position < len(tree) - 1:
        raise TrailingCharsError(position + 1)
    elif len(bracket_positions) > 0:
        raise MissingRBError(bracket_positions.pop())

def main():
    tree = ''.join([line.strip() for line in sys.stdin.readlines()])
    try:
        check_tree(tree)
    except BaseError as error:
        sys.stderr.write('### error: {0}\n'.format(str(error)))
        return 1
    else:
        return 0

if __name__ == '__main__':
    status = main()
    sys.exit(status)

