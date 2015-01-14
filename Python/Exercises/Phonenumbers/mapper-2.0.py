#!/usr/bin/env python

from argparse import ArgumentParser
import os, sys

class Mapper(object):

    def __init__(self, dict_file_name):
        self._mapping = {
            '2': 'abc',
            '3': 'def',
            '4': 'ghi',
            '5': 'jkl',
            '6': 'mno',
            '7': 'pqrs',
            '8': 'tuv',
            '9': 'wxyz'}
        self._dictionary = self.read_dict(dict_file_name)

    def read_dict(self, dict_file_name):
        dictionary = []
        with open(dict_file_name) as dict_file:
            for line in dict_file.readlines():
                word = line.strip()
                if word.isalpha():
                    dictionary.append(word.lower())
        return dictionary

    def map(self, phone_number):
        words = self._dictionary
        for idx, digit in enumerate(phone_number):
            if digit in self._mapping:
                chars = self._mapping[digit]
                words = [word for word in words if idx < len(word) and word[idx] in chars]
        return words

def main():
    arg_parser = ArgumentParser(description='convert phone number to'
                                            ' English word, if possible')
    arg_parser.add_argument('-dict', dest='dict_name',
                            default='/usr/share/dict/words',
                            help='dictionary file to use')
    options = arg_parser.parse_args()
    mapper = Mapper(options.dict_name)
    for line in sys.stdin:
        phone_number = line.strip()
        words = mapper.map(phone_number)
        print phone_number, ':', ','.join(words)
    return 0

if __name__ == '__main__':
    status = main()
    sys.exit(status)


