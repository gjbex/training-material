#!/usr/bin/env python

import os
import shutil
import sqlite3
import unittest


class ContentsTest(unittest.TestCase):

    master_name = 'projects.db'
    test_name = 'test.db'

    @classmethod
    def setUpClass(cls):
        '''copy original database'''
        shutil.copyfile(cls.master_name, cls.test_name)

    def setUp(self):
        '''open connection, create cursor'''
        self._conn = sqlite3.connect(self.__class__.test_name)
        self._conn.row_factory = sqlite3.Row
        self._cursor = self._conn.cursor()

    def tearDown(self):
        '''close database connection'''
        self._conn.close()

    @classmethod
    def tearDownClass(cls):
        '''remove test database'''
        os.remove(cls.test_name)

    def test_num_projects(self):
        '''test whether the projects table has the expected number of
           rows'''
        expected = 3
        self._cursor.execute(''' SELECT COUNT(*) FROM projects;''')
        nr_rows = self._cursor.fetchone()[0]
        self.assertEqual(expected, nr_rows)

    def test_num_researchers(self):
        '''test whether the researchers table has the expected number of
           rows'''
        expected = 3
        self._cursor.execute(''' SELECT COUNT(*) FROM researchers;''')
        nr_rows = self._cursor.fetchone()[0]
        self.assertEqual(expected, nr_rows)

    def test_num_assignments(self):
        '''test whether the number of staff assignments is the expected
           number'''
        expected = 2
        self._cursor.execute(''' SELECT COUNT(*) FROM staff_assignments;''')
        nr_rows = self._cursor.fetchone()[0]
        self.assertEqual(expected, nr_rows)

    def test_view_consistency(self):
        '''test whether the staff assignments table has the same number
           of rows as the project staffing view'''
        self._cursor.execute(''' SELECT COUNT(*) FROM staff_assignments;''')
        nr_table_rows = self._cursor.fetchone()[0]
        self._cursor.execute(''' SELECT COUNT(*) FROM project_staffing;''')
        nr_view_rows = self._cursor.fetchone()[0]
        self.assertEqual(nr_table_rows, nr_view_rows)

    def test_researcher_bob(self):
        '''test whether there is a researcher named Bob, and whether
           his last name is Dreary'''
        expected_last_name = 'Dreary'
        expected_nr_rows = 1
        self._cursor.execute(
            '''SELECT last_name FROM researchers
                   WHERE first_name = ?;''',
            ('Bob', )
        )
        nr_rows = 0
        last_name = None
        for row in self._cursor:
            nr_rows += 1
            last_name = row['last_name']
        self.assertEqual(expected_nr_rows, nr_rows)
        self.assertEqual(expected_last_name, last_name)

    def test_projects_start_date(self):
        '''test whether the projects table has the correct number of
           projects starting before November 1, 2014, and check those are
           the expected projects'''
        expected_projects = ['project 1', 'project 2']
        self._cursor.execute(
            '''SELECT project_name FROM projects
                  WHERE start_date < ?
                  ORDER BY project_name ASC;''',
            ('2014-11-01', )
        )
        projects = []
        for row in self._cursor:
            projects.append(row['project_name'])
        self.assertListEqual(expected_projects, projects)

    def test_unassigned_researchers(self):
        '''test whether the number of unassigned researchers is the
           expected one, and that Carol is idle'''
        expected_researchers = ['Carol']
        self._cursor.execute(
            '''SELECT first_name FROM researchers
                   WHERE researcher_id IN (
                       SELECT researcher_id
                           FROM researchers
                       EXCEPT SELECT researcher_id
                               FROM staff_assignments);'''
        )
        researchers = []
        for row in self._cursor:
            researchers.append(row['first_name'])
        self.assertListEqual(expected_researchers, researchers)

    def test_assigned_projects(self):
        '''test whether the expected number of projects has been
           assigned'''
        expected_nr_assignments = 2
        self._cursor.execute(
            '''SELECT COUNT(DISTINCT project_id) FROM staff_assignments;'''
        )
        nr_assignments = self._cursor.fetchone()[0]
        self.assertEqual(expected_nr_assignments, nr_assignments)

    def test_samples_per_project(self):
        '''tset whether each project has the correct number of samples
           associated with it'''
        expected_samples = {
            'project 1': {'homo sapiens', 'felis catus'},
            'project 2': {'felis catus'},
            'project 3': set(),
        }
        self._cursor.execute(
            '''SELECT p.project_name AS 'project_name',
                      COUNT(s.sample_id) AS 'nr_samples'
                   FROM projects AS p, samples AS s
                   WHERE s.project_id = p.project_id
                   GROUP BY p.project_id;'''
        )
        for row in self._cursor:
            self.assertEqual(len(expected_samples[row['project_name']]),
                             row['nr_samples'])
        for project_name in expected_samples:
            self._cursor.execute(
                '''SELECT s.organism AS organism
                       FROM projects AS p, samples AS s
                       WHERE p.project_name = ? AND
                             p.project_id = s.project_id;''',
                (project_name, )
            )
            samples = set()
            for row in self._cursor:
                samples.add(row['organism'])
            self.assertSetEqual(expected_samples[project_name], samples)


if __name__ == '__main__':
    unittest.main()
