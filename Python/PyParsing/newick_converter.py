#!/usr/bin/env python
'''various implementations of tree writers'''

from argparse import ArgumentParser, FileType
from tree_converter import XmlWriter, IndentedStringWriter, RelationalWriter
from newick_parser import NewickParser


class XmlNewickWriter(XmlWriter):
    '''Writes a given node and its children as XML'''

    def node_attr(self, node):
        '''formats node attributes, if any'''
        attr = ''
        if node.label is not None:
            attr += ' label="{0}"'.format(node.label)
        if node.length is not None:
            attr += ' length="{0}"'.format(node.length)
        return attr


class IndentedStringNewickWriter(IndentedStringWriter):
    '''Writes a given node and its children as an indented string'''

    def node_attr(self, node):
        '''formats node attributes, if any'''
        attr = ''
        if node.label is not None:
            attr += ': {0}'.format(node.label)
        if node.length is not None:
            attr += '[{0}]'.format(node.length)
        return attr


class RelationalNewickWriter(RelationalWriter):
    '''Writes a given node and its children in a form that can be stored in
       a relational table'''

    def node_attr(self, node):
        '''formats node attributes, if any'''
        attr = ''
        if node.label is not None:
            attr += '\t{0}'.format(node.label)
        else:
            attr += '\tNone'
        if node.length is not None:
            attr += '\t{0}'.format(node.length)
        else:
            attr += '\tNone'
        return attr


def main():
    '''Function that will parse the given file and convert the tree to the
       format specified'''
    argParser = ArgumentParser(description='tree structured data converter')
    argParser.add_argument('--file', type=FileType('r'), action='store',
                           dest='file', required=True,
                           help='file to parse')
    argParser.add_argument('--format', type=str, action='store',
                           default='string', dest='format',
                           help='format to convert to, default = string')
    options = argParser.parse_args()
    tree_str = '\n'.join(options.file.readlines())
    options.file.close()
    node_parser = NewickParser()
    tree = node_parser.parse(tree_str)
    if options.format == 'xml':
        writer = XmlNewickWriter()
    elif options.format == 'relational':
        writer = RelationalNewickWriter()
    else:
        writer = IndentedStringNewickWriter()
    print(writer.write(tree))

if __name__ == '__main__':
    main()
