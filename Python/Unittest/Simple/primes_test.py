#!/usr/bin/env python

import unittest
from func_lib import primes


class PrimesTest(unittest.TestCase):
    '''Tests the functions in the func_lib module'''

    def test_primes_list(self):
        '''test primes'''
        expected = [2, 3, 5, 7, 11, 13, 17]
        self.assertListEqual(expected, primes(18))


if __name__ == '__main__':
    unittest.main()
