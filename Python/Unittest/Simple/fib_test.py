#!/usr/bin/env python

import unittest
from func_lib import fib, InvalidArgumentException


class FibTest(unittest.TestCase):
    '''Tests the functions in the func_lib module'''

    def test_low_values(self):
        '''test a number computations for small arguments'''
        expected = [1, 1, 2, 3, 5, 8, 13]
        for i in range(len(expected)):
            with self.subTest(i=i):
                self.assertEqual(expected[i], fib(i))

    def test_negative_values(self):
        '''test for call with negative argument'''
        with self.assertRaises(InvalidArgumentException):
            fib(-1)


if __name__ == '__main__':
    unittest.main()
