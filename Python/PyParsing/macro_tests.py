#!/usr/bin/env python
'''Module defining some unit tests for the MacroExpander utility'''

import unittest
from macro_expander import MacroExpander


class MacroExapnderTest(unittest.TestCase):

    def setUp(self):
        self._expander = MacroExpander()
        self._expander.add_macro('upper', lambda x: x.upper())
        self._expander.add_macro('lower', lambda x: x.lower())
        self._expander.add_macro('gjb', lambda: 'Geert Jan Bex')
        self._expander.add_macro('repeat', lambda x, n: int(n)*x)
        self._expander.add_macro('cat', lambda x, y: x + '-' + y)
        self._expander.add_macro('add', lambda x, y: str(int(x) + int(y)))

    def test_upper(self):
        orig_text = 'This is a text with \\upper{a function call}.'
        target_text = 'This is a text with A FUNCTION CALL.'
        text = self._expander.expand(orig_text)
        self.assertEqual(text, target_text)

    def test_apostrophe(self):
        orig_text = "This'll be upper case \\upper{won't it?}."
        target_text = "This'll be upper case WON'T IT?."
        text = self._expander.expand(orig_text)
        self.assertEqual(text, target_text)

    def test_multiple_arguments(self):
        orig_text = 'This \cat{abc}{def} a text.'
        target_text = 'This abc-def a text.'
        text = self._expander.expand(orig_text)
        self.assertEqual(text, target_text)

    def test_numerical_arguments(self):
        orig_text = 'This is a sum: \\add{3}{7}.'
        target_text = 'This is a sum: 10.'
        text = self._expander.expand(orig_text)
        self.assertEqual(text, target_text)

    def test_literal_string(self):
        orig_text = r'This \repeat{is}{3} a text.'
        target_text = 'This isisis a text.'
        text = self._expander.expand(orig_text)
        self.assertEqual(text, target_text)

    def test_multiple_macros(self):
        orig_text = ('This \\repeat{is}{3} a text with \\upper{a ' +
                     'function call}.')
        target_text = 'This isisis a text with A FUNCTION CALL.'
        text = self._expander.expand(orig_text)
        self.assertEqual(text, target_text)

    def test_multiple_lines(self):
        orig_text = ('This is a text with \\upper{a function call},\n' +
                     'and \lower{ANOTHER ONE} on multiple lines\n\n' +
                     'authored by... \gjb.\n')
        target_text = ('This is a text with A FUNCTION CALL,\n' +
                       'and another one on multiple lines\n\n' +
                       'authored by... Geert Jan Bex.\n')
        text = self._expander.expand(orig_text)
        self.assertEqual(text, target_text)


if __name__ == '__main__':
    unittest.main()
