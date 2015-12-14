#!/usr/bin/env python

import unittest
from func_lib import is_prime, InvalidArgumentException


class IsPrimeTest(unittest.TestCase):
    '''Tests the functions in the func_lib module'''

    def test_primes(self):
        '''test is_prime for prime numbers'''
        primes = [2, 3, 5, 7, 11, 13, 17]
        for prime in primes:
            with self.subTest(i=prime):
                self.assertTrue(is_prime(prime))

    def test_non_primes(self):
        '''test is_prime for non-prime numbers'''
        non_primes = [0, 1, 4, 6, 9]
        for non_prime in non_primes:
            with self.subTest(i=non_prime):
                self.assertFalse(is_prime(non_prime))

    def test_invalid_argument(self):
        '''test for exception with negative argument'''
        with self.assertRaises(InvalidArgumentException):
            is_prime(-1)


if __name__ == '__main__':
    unittest.main()
