#!/usr/bin/env python
'''various implementations of tree writers'''

from argparse import ArgumentParser, FileType
from node_parser import NodeParser


class XmlWriter:
    '''Writes a given node and its children as XML'''

    def write(self, node):
        '''Writes the given node and its children as XML'''
        repr = '<node name="{0}"'.format(node.name)
        repr += self.node_attr(node)
        if node.nr_children() > 0:
            repr += '>'
            for child in node.children():
                repr += self.write(child)
            repr += '</node>'
        else:
            repr += '/>'
        return repr

    def node_attr(self, node):
        '''formats node attributes, if any'''
        return ''


class IndentedStringWriter:
    '''Writes a given node and its children as an indented string'''

    def write(self, node, level=0):
        '''compute a string representaion starting from
           this node down'''
        repr = '{0}node "{1}"'.format(level*'  ', node.name)
        repr += self.node_attr(node) + '\n'
        for child in node.children():
            repr += self.write(child, level + 1)
        return repr

    def node_attr(self, node):
        '''formats node attributes, if any'''
        return ''


class RelationalWriter:
    '''Writes a given node and its children in a form that can be stored in
       a relational table'''

    def write(self, node):
        '''compute a string representation suitable for storage in a
           relational table'''
        current_id = 0
        id_dict = {node: current_id}
        repr = '{0}\t{1}\t{2}'.format(id_dict[node], None, node.name)
        repr += self.node_attr(node) + '\n'
        queue = [node]
        while len(queue) > 0:
            current = queue.pop(0)
            for child in current.children():
                current_id += 1
                id_dict[child] = current_id
                repr += '{0}\t{1}\t{2}'.format(id_dict[child],
                                               id_dict[current],
                                               child.name)
                repr += self.node_attr(child) + '\n'
                queue.append(child)
        return repr

    def node_attr(self, node):
        '''formats node attributes, if any'''
        return ''


def main():
    '''Function that will parse the given file and convert the tree to the
       format specified'''
    arg_parser = ArgumentParser(description='tree structured data '
                                            'converter')
    arg_parser.add_argument('file', type=FileType('r'),
                            help='file to parse')
    arg_parser.add_argument('--format', type=str, default='string',
                            help='format to convert to, default = string')
    options = arg_parser.parse_args()
    tree_str = '\n'.join(options.file.readlines())
    options.file.close()
    node_parser = NodeParser()
    node_parser.parse(tree_str)
    tree = node_parser.node()
    if options.format == 'xml':
        writer = XmlWriter()
    elif options.format == 'relational':
        writer = RelationalWriter()
    else:
        writer = IndentedStringWriter()
    print(writer.write(tree))

if __name__ == '__main__':
    main()
