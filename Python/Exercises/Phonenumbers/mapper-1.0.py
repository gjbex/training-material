#!/usr/bin/env python

from argparse import ArgumentParser
import sys


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
            for line in dict_file:
                word = line.strip()
                if word.isalpha():
                    dictionary.append(word.lower())
        return dictionary

    def map(self, phone_number):
        words = ['']
        for digit in phone_number:
            words = self.extend(words, digit)
        return [
            word_candidate
            for word_candidate in words
            if self.is_word(word_candidate)
        ]

    def is_prefix(self, word_prefix):
        return any(word.startswith(word_prefix) for word in self._dictionary)

    def is_word(self, word_candidate):
        return any(word == word_candidate for word in self._dictionary)

    def extend(self, words, digit):
        new_words = []
        if digit in self._mapping:
            for word in words:
                for character in self._mapping[digit]:
                    new_word = word + character
                    if self.is_prefix(new_word):
                        new_words.append(new_word)
        return new_words


def main():
    arg_parser = ArgumentParser(description='convert phone number to'
                                            ' English word, if possible')
    arg_parser.add_argument('phone_number', help='phone number to convert')
    arg_parser.add_argument('-dict', dest='dict_name',
                            default='/usr/share/dict/words',
                            help='dictionary file to use')
    options = arg_parser.parse_args()
    mapper = Mapper(options.dict_name)
    words = mapper.map(options.phone_number)
    if len(words) > 0:
        for word in words:
            print(word)
        return 0
    else:
        sys.stderr.write('### warming: no words found\n')
        return 1

if __name__ == '__main__':
    status = main()
    sys.exit(status)
