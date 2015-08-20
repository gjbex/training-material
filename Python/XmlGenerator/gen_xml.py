#!/usr/bin/env python

from argparse import ArgumentParser
import math
import random
import string
import sys
from xml.dom.minidom import Document


class Tags(object):

    def __init__(self, size, base='a'):
        digits = int(math.log10(size)) + 1
        self._format_str = '{base}{{index:0{digits}d}}'.format(base=base,
                                                               digits=digits)
        self._size = size

    @property
    def size(self):
        return self._size

    def random(self):
        index = random.randint(0, self._size - 1)
        return self._format_str.format(index=index)


class Texts(object):

    def __init__(self, size):
        self._size = size

    def random(self):
        return ''.join([random.choice(string.ascii_lowercase)
                       for _ in range(random.randint(1, self._size))])


class Docs(object):

    def __init__(self, size, tags, text_prob, texts=None):
        self._size = size
        self._tags = tags
        self._generate_text = text_prob > 1.0e-10
        self._text_prob = text_prob
        self._texts = texts

    @property
    def size(self):
        return self._size

    def random(self):
        doc = Document()
        node_list = []
        for _ in range(self._size):
            tag = self._tags.random()
            element = doc.createElement(tag)
            if node_list:
                parent = random.choice(node_list)
            else:
                parent = doc
            parent.appendChild(element)
            node_list.append(element)
        for element in node_list:
            if random.random() < self._text_prob:
                text_value = self._texts.random()
                text = doc.createTextNode(text_value)
                element.appendChild(text)
        return doc


def main():
    arg_parser = ArgumentParser('creates XML encoded block data')
    arg_parser.add_argument('--tags', type=int, action='store',
                            dest='nr_tags', help='number of tags to use')
    arg_parser.add_argument('--elements', type=int, action='store',
                            dest='nr_elements',
                            help='number of elements in document')
    arg_parser.add_argument('--text-prob', action='store', type=float,
                            dest='text_prob', default=0.0,
                            help='probability to generate text in elements')
    arg_parser.add_argument('--text-length', type=int, action='store',
                            dest='max_text_length', default=5,
                            help='number of elements in document')
    options = arg_parser.parse_args()
    if not options.nr_tags:
        options.nr_tags = random.randint(1, 10)
    if not options.nr_elements:
        options.nr_elements = random.randint(1, 10)
    tags = Tags(options.nr_tags)
    texts = Texts(options.max_text_length)
    docs = Docs(options.nr_elements, tags, options.text_prob, texts)
    doc = docs.random()
    print(doc.toprettyxml(indent='  '))
    return 0

if __name__ == '__main__':
    status = main()
    sys.exit(status)
