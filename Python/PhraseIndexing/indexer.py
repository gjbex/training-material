#!/usr/bin/env python

import sys


class Indexer(object):
    '''An Indexer can parse a text file, using a phrase dictionary, and
       record for each phrase the line number it occurs on in the
       text'''

    def __init__(self, window_size=10, read_length=1024,
                 progress_line_nr=1000):
        '''constructor, takes configuration options for the Indexer
           the window size, i.e., the maximal length of phrases to
           index, read_length, i.e., the buffer length for file read
           operations, and progress line numbers, i.e., the number of
           lines after which to report indexing progress'''
        self._phrases = None
        self._window = []
        self._window_size = window_size
        self._line_nr = 0
        self._read_length = read_length
        self._progress_line_nr = progress_line_nr

    def _check_window(self):
        '''private method to check whether the current window contains
           phrases that have to be indexed, if so, record line numbers'''
        for i in range(len(self._window)):
            phrase = ' '.join(self._window[i:])
            if phrase in self._phrases:
                self._phrases[phrase].append(self._line_nr)

    def parse(self, text_file_name, phrases, show_progress=False):
        '''parse a text file, and store index in the provided phrase
           dictionary, write progress information if show_progress is
           True'''
        self._phrases = phrases
        with open(text_file_name, 'r', newline='') as text_file:
            word = ''
            while buffer := text_file.read(self._read_length):
                for character in buffer:
                    if character.isalpha():
                        word += character
                    else:
                        if word:
                            if len(self._window) == self._window_size:
                                self._window.pop(0)
                            self._window.append(word)
                            self._check_window()
                            word = ''
                        if character == '\n':
                            self._line_nr += 1
                            if (show_progress and
                                self._line_nr % self._progress_line_nr == 0):
                                msg = 'parsing line {0:d}\n'
                                sys.stderr.write(msg.format(self._line_nr))
        return self._phrases

if __name__ == '__main__':
    from argparse import ArgumentParser

    arg_parser = ArgumentParser(description='index phrases in text')
    arg_parser.add_argument('--phrases', required=True,
                            help='text file containing a list of phrases, '
                                 'one per line')
    arg_parser.add_argument('--text', required=True,
                            help='text file')
    arg_parser.add_argument('--read_length', type=int, default=16*1024,
                            help='size of the read buffer')
    arg_parser.add_argument('--verbose', action='store_true',
                            help='provide some feedback')
    options = arg_parser.parse_args()

# read the phrase book, and initialize the dictionary, and determine
# longest phrase
    phrases = {}
    max_phrase_len = 0
    with open(options.phrases, 'r') as phrases_file:
        for line in phrases_file:
            if phrase := line.strip():
                phrases[line.strip()] = []
                max_phrase_len = max(len(line.split(' ')), max_phrase_len)
    if options.verbose:
        msg = '{0:d} phrases, max. length = {1:d}\n'
        sys.stderr.write(msg.format(len(phrases), max_phrase_len))

# create an Indexer, and parse the text file
    indexer = Indexer(window_size=max_phrase_len,
                      read_length=options.read_length)
    indexer.parse(options.text, phrases, show_progress=options.verbose)

# print results
    for phrase in phrases:
        print('{0}: {1}'.format(phrase,
                                ', '.join([str(x)
                                           for x in phrases[phrase]])))
