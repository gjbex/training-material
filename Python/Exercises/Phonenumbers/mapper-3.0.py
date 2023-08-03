#!/usr/bin/env python

from argparse import ArgumentParser
import re
import sys


class Mapper(object):

    def __init__(self, dict_file_name):
        self._mapping = {
            '0': r'',
            '1': r'',
            '2': r'[abc]',
            '3': r'[def]',
            '4': r'[ghi]',
            '5': r'[jkl]',
            '6': r'[mno]',
            '7': r'[pqrs]',
            '8': r'[tuv]',
            '9': r'[wxyz]'}
        self._dictionary = self.read_dict(dict_file_name)

    def read_dict(self, dict_file_name):
        dictionary = []
        with open(dict_file_name) as dict_file:
            for line in dict_file:
                word = line.strip()
                if word.isalpha():
                    dictionary.append(word.lower())
        return dictionary

    def map(self, phone_number):
        regex_str = r''.join(self._mapping[digit] for digit in phone_number) + r'\w*$'
        regex = re.compile(regex_str)
        return [word for word in self._dictionary if regex.match(word) is not None]


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
        print(phone_number, ':', ','.join(words))
    return 0

if __name__ == '__main__':
    status = main()
    sys.exit(status)
