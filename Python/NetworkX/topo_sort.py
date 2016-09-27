#!/usr/bin/env python

from argparse import ArgumentParser
import networkx as nx


class Reference(object):

    def __init__(self, author, title, journal, year):
        self._author = author
        self._title = title
        self._journal = journal
        self._year = year
        self._key = None

    @property
    def author(self):
        return self._author

    @property
    def title(self):
        return self._title

    @property
    def journal(self):
        return self._journal

    @property
    def year(self):
        return self._year

    @property
    def key(self):
        return self._key

    @key.setter
    def key(self, ref_key):
        self._key = ref_key

    def format(self):
        fmt_str = '[{key}] {author} "{title}", {journal}, {year}'
        return fmt_str.format(key=self.key, author=self.author,
                              title=self.title, journal=self.journal,
                              year=self.year)
    def __str__(self):
        return self.key


def create_refs():
    refs = {
        'A01': Reference(
                    author='Alice',
                    title='Encryption with blowfish',
                    journal='Security research',
                    year=2001,),
        'B02a': Reference(
                    author='Bob',
                    title='Applying blowfish for fun and profit',
                    journal='Security research',
                    year=2002,),
        'B02b': Reference(
                    author='Bob',
                    title='Applying blowfish for email encryption',
                    journal='Security research',
                    year=2002,),
        'C03': Reference(
                    author='Carol',
                    title='Pufferfish: a new encryption algorithm',
                    journal='Notices of the Luxemburg Academy of Sciences',
                    year=2003,),
        'E02': Reference(
                    author='Eve',
                    title='Hacking blowfish',
                    journal='Hacker magazine',
                    year=2002,),
        'T04': Reference(
                    author='Trent',
                    title='Review of modern encryption systems',
                    journal='ACM Research on Security',
                    year=2004,),
        'A03': Reference(
                    author='Alice',
                    title='Proving blowfish to be mathemattically secure',
                    journal='Security research',
                    year=2003,),
    }
    for key in refs:
        refs[key].key = key
    return refs


def create_graph():
    refs = create_refs()
    citations = nx.DiGraph()
    citations.add_edge(refs['A01'], refs['B02a'])
    citations.add_edge(refs['A01'], refs['B02b'])
    citations.add_edge(refs['A01'], refs['E02'])
    citations.add_edge(refs['A01'], refs['A03'])
    citations.add_edge(refs['A01'], refs['T04'])
    citations.add_edge(refs['B02a'], refs['B02b'])
    citations.add_edge(refs['B02a'], refs['T04'])
    citations.add_edge(refs['E02'], refs['T04'])
    citations.add_node(refs['C03'])
    return citations


def show_sorted(G):
    nodes = nx.algorithms.topological_sort(G)
    print('\n'.join([n.format() for n in nodes]))

if __name__ == '__main__':
    arg_parser = ArgumentParser(description='illustration of topological '
                                            'sort')
    options = arg_parser.parse_args()
    G = create_graph()
    show_sorted(G)
