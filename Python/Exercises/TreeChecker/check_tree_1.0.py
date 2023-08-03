#!/usr/bin/env python

import sys


def is_tree_ok(tree):
    nr_open_brackets = 0
    nr_characters = 0
    for character in tree:
        nr_characters += 1
        if character == '(':
            nr_open_brackets += 1
        elif character == ')':
            nr_open_brackets -= 1
        if nr_open_brackets == 0:
            break
    if nr_open_brackets == 0 and nr_characters < len(tree):
        return False
    return nr_open_brackets == 0


def main():
    tree = ''.join([line.strip() for line in sys.stdin.readlines()])
    if is_tree_ok(tree):
        return 0
    print('### error in tree')
    return 1

if __name__ == '__main__':
    status = main()
    sys.exit(status)
