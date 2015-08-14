import os
import unittest

from constant_db import ConstantDb, UnknownConstantError


class ConstantDbTest(unittest.TestCase):

    def setUp(self):
        self.file_name = 'test.db'
        self.db = ConstantDb(self.file_name)
        self.db.init()

    def test_g_value(self):
        expected_value = 9.81
        value = self.db.get_value('g')
        self.assertAlmostEqual(expected_value, value, 1.0e-4)

    def test_constant_names(self):
        expected_names = {'g', 'pi', 'mach'}
        names = self.db.get_names()
        for name in names:
            self.assertIn(name, expected_names)

    def test_constant_unknown(self):
        self.assertRaises(UnknownConstantError, self.db.get_value, 'c')

    def test_nr_constants(self):
        expected_nr_constants = 3
        nr_constats = self.db.get_nr_constants()
        self.assertEquals(expected_nr_constants, nr_constats,
                          'This test is supposed to fail by way '
                          'of illustration')

    def tearDown(self):
        self.db.close()
        os.remove(self.file_name)
