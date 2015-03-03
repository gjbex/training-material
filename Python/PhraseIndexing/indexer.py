#!/usr/bin/env python

import sys

class Indexer(object):

    def __init__(self, phrases, window_size=10, read_length=1024,
                 progress_line_nr=1000):
        self._phrases = phrases
        self._window = []
        self._window_size = window_size
        self._line_nr = 0
        self._read_length = read_length
        self._progress_line_nr = progress_line_nr

    def is_window_full(self):
        return len(self._window) == self._window_size

    def check_window(self):
        for i in xrange(len(self._window)):
            phrase = ' '.join(self._window[i:])
            if phrase in self._phrases:
                self._phrases[phrase].append(self._line_nr)

    def parse(self, text_file_name, show_progress=False):
        with open(text_file_name, 'rb') as text_file:
            word = ''
            buffer = text_file.read(self._read_length)
            while buffer:
                for character in buffer:
                    if character.isalpha():
                        word += character
                    else:
                        if word:
                            if self.is_window_full():
                                self._window.pop(0)
                            self._window.append(word)
                            self.check_window()
                            word = ''
                        if character == '\n':
                            self._line_nr += 1
                            if (show_progress and
                                self._line_nr % self._progress_line_nr == 0):
                                msg = 'parsing line {0:d}\n'
                                sys.stderr.write(msg.format(self._line_nr))
                buffer = text_file.read(self._read_length)
        return self._phrases

if __name__ == '__main__':
    from argparse import ArgumentParser

    arg_parser = ArgumentParser(description='index phrases in text')
    arg_parser.add_argument('--phrases', required=True,
                            help='text file containing a list of phrases, '
                                 'one per line')
    arg_parser.add_argument('--text', required=True,
                            help='text file')
    arg_parser.add_argument('--verbose', action='store_true',
                            help='provide some feedback')
    options = arg_parser.parse_args()

# read the phrase book, and initialize the dictionary, and determine
# longest phrase
    phrases = {}
    max_phrase_len = 0
    with open(options.phrases, 'r') as phrases_file:
        for line in phrases_file:
            phrase = line.strip()
            if phrase:
                phrases[line.strip()] = []
                max_phrase_len = max(len(line.split(' ')), max_phrase_len)
    if options.verbose:
        msg = '{0:d} phrases, max. length = {1:d}\n'
        sys.stderr.write(msg.format(len(phrases), max_phrase_len))

# create an Indexer, and parse the text file
    indexer = Indexer(phrases, window_size=max_phrase_len)
    indexer.parse(options.text, show_progress=options.verbose)

# print results
    for phrase in phrases:
        print '{0}: {1}'.format(phrase, ', '.join([str(x) for x in phrases[phrase]]))
