#!/usr/bin/env python

import unittest
from func_lib import pi


class PiTest(unittest.TestCase):
    '''Tests the functions in the func_lib module'''

    def test_pi_low_precision(self):
        '''test pi function for few integration points'''
        expected = 3.14159265359
        self.assertAlmostEqual(expected, pi(1000), places=2)

    def test_pi_high_precision(self):
        '''test pi function for many integration points'''
        expected = 3.14159265359
        self.assertAlmostEqual(expected, pi(1000000), places=5)


if __name__ == '__main__':
    unittest.main()
