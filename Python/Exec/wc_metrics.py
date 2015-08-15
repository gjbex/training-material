#!/usr/bin/env python

from argparse import ArgumentParser
from subprocess import check_output, CalledProcessError, STDOUT


class WcInfo:

    def __init__(self, out_str):
        data = out_str.strip().split(' ')
        self._name = data[3]
        self._lines = int(data[0])
        self._words = int(data[1])
        self._chars = int(data[2])

    @property
    def name(self):
        return self._name

    @property
    def lines(self):
        return self._lines

    @property
    def words(self):
        return self._words

    @property
    def chars(self):
        return self._chars

    def __str__(self):
        return (
            '{name}:' +
            '\n  lines = {lines}' +
            '\n  words = {words}' +
            '\n  chars = {chars}').format(
                name=self.name,
                lines=self.lines,
                words=self.words,
                chars=self.chars)


def compute_stats(wc):
    return (
        'avg chars/word = {cpw:.2f}\n' +
        'avg chars/line = {cpl:.2f}\n' +
        'avg words/line = {wpl:.2f}').format(
            cpw=float(wc.chars)/wc.words,
            cpl=float(wc.chars)/wc.lines,
            wpl=float(wc.words)/wc.lines)


def main():
    arg_parser = ArgumentParser(description='compute word count stats')
    arg_parser.add_argument('files', nargs='+',
                            help='files to compute stats for')
    args = arg_parser.parse_args()
    for f in args.files:
        try:
            stats = check_output(['wc', f], stderr=STDOUT)
            wc_info = WcInfo(stats.decode(encoding='utf-8'))
            print(wc_info)
            print(compute_stats(wc_info))
        except CalledProcessError as e:
            print(e)

if __name__ == '__main__':
    main()
