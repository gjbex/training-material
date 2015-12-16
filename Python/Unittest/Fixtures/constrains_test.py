#!/usr/bin/env python

import os
import shutil
import sqlite3
import unittest


class ConstrainsTest(unittest.TestCase):
    '''tests the table constrains and triggers defined on the schema'''

    def setUp(self):
        '''copy original database, and open connection, create cursor'''
        master_name = 'projects.db'
        self._test_name = 'test.db'
        shutil.copyfile(master_name, self._test_name)
        self._conn = sqlite3.connect(self._test_name)
        self._conn.row_factory = sqlite3.Row
        self._cursor = self._conn.cursor()

    def tearDown(self):
        '''close database connection and remove test database'''
        self._conn.close()
        os.remove(self._test_name)

    def test_project_end_date(self):
        '''inserting a project with an invaid end date should fail'''
        project_name = 'project 4'
        start_date = '2015-01-05'
        end_date = '2014-12-15'
        with self.assertRaises(sqlite3.IntegrityError):
            self._cursor.execute(
                '''INSERT INTO projects (project_name, start_date, end_date)
                       VALUES (?, ?, ?);''',
                (project_name, start_date, end_date)
            )

if __name__ == '__main__':
    unittest.main()
