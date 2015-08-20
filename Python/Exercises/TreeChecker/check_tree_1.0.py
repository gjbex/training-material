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
    if nr_open_brackets != 0:
        return False
    return True


def main():
    tree = ''.join([line.strip() for line in sys.stdin.readlines()])
    if not is_tree_ok(tree):
        print('### error in tree')
        return 1
    else:
        return 0

if __name__ == '__main__':
    status = main()
    sys.exit(status)
