#!/usr/bin/env python

from argparse import ArgumentParser, FileType
import imp
import sys
import types
from pyparsing import Regex, Literal, ZeroOrMore, Group


class UndefinedMacroError(Exception):
    '''Class encoding an exception for an undefined macro encountered
       while parsing a text'''

    def __init__(self, function_name):
        '''Constructor, takes the unknown macro name as an argument'''
        super(UndefinedMacroError, self).__init__()
        self._msg = "unknown macro '{0}'".format(function_name.strip('\\'))

    def __str__(self):
        '''method to stringify the exception'''
        return repr(self._msg)


class MacroExpander(object):
    '''Macro expansion class, macros are encoded as
       \\macro_name{param_1}...{param_n}'''

    def __init__(self):
        '''Constructor'''
        self._macros = {}
        text = Regex(r'[^\\]+').leaveWhitespace()
        lb = Literal('{').suppress()
        rb = Literal('}').suppress()
        param_value = Regex(r'[^}\\]+')
        param = lb + ZeroOrMore(param_value) + rb
        params = Group(ZeroOrMore(param)).setResultsName('params')
        macro_name = Regex(r'\\\w+').setResultsName('macro')
        macro_call = macro_name + params
        text_file = ZeroOrMore(text | macro_call)

        def macro_action(toks):
            macro_name = toks['macro']
            params = toks['params']
            if self._has_macro(macro_name):
                return self._macros[macro_name](*params)
            else:
                raise UndefinedMacroError(macro_name)
        macro_call.addParseAction(macro_action)
        self._grammar = text_file

    def add_macro(self, macro_name, macro_impl):
        '''method to add a new macro to the macro expander, given
           the function name, and its implementation as arguments'''
        self._macros['\\' + macro_name] = macro_impl

    def _has_macro(self, macro_name):
        '''internal method to check whether the parser has a
           definition for the given macro name'''
        return macro_name in self._macros

    def expand(self, text):
        '''method to perform the macro expansion on the given text'''
        results = self._grammar.parseString(text)
        return ''.join(results)


def main():
    arg_parser = ArgumentParser(description='macro expansion utility')
    arg_parser.add_argument('--file', type=FileType('r'),
                            action='store', dest='file',
                            required=True, help='file to expand')
    arg_parser.add_argument('--def', type=str, action='store',
                            default='macro_defs', dest='defs',
                            help='macro definitions module name')
    try:
        options = arg_parser.parse_args()
        text = ''.join(options.file)
        module_info = imp.find_module(options.defs)
        macro_module = imp.load_module(options.defs, *module_info)
        expander = MacroExpander()
        for macro_def in macro_module.__dict__.values():
            if isinstance(macro_def, types.FunctionType):
                expander.add_macro(macro_def.__name__, macro_def)
        print(expander.expand(text))
    except UndefinedMacroError as error:
        sys.stderr.write('### error: ' + str(error) + '\n')
        sys.exit(2)
    except Exception as error:
        sys.stderr.write('### error: ' + str(error) + '\n')
        sys.exit(1)

if __name__ == '__main__':
    main()
