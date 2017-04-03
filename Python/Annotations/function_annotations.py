#!/usr/bin/env python

from typing import Sequence, TypeVar, Dict

T = TypeVar('T')


def count_chars(sequence: Sequence[T]) -> Dict[T, int]:
    counter = {}
    for element in sequence:
        if element not in counter:
            counter[element] = 0
        counter[element] += 1
    return counter

if __name__ == '__main__':
    seq = 'AGGTCCTGGA-GGTAC'
    counter = count_chars(seq)
    func_name = count_chars.__name__
    func_return = count_chars.__annotations__['return']
    print('function {name}\n\treturns {rtype}'.format(name=func_name,
                                                      rtype=func_return))
    print('\targuments:')
    for arg, atype in count_chars.__annotations__.items():
        if arg != 'return':
            print('\t\t{arg}: {type}'.format(arg=arg, type=atype))
    for element, count in counter.items():
        print('{e}: {c:d}'.format(e=element, c=count))
