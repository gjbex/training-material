#!/usr/bin/env python

import os
import shutil
import sqlite3
import unittest

import init_db


'''name of database to use as master'''
master_name = 'projects.db'


def setUpModule():
    '''create and fill the database'''
    conn = sqlite3.connect(master_name)
    init_db.execute_file(conn, 'create_db.sql')
    init_db.execute_file(conn, 'fill_db.sql')


def tearDownModule():
    '''remove database file once testing is done'''
    os.remove(master_name)


class ContentsTest(unittest.TestCase):

    test_name = 'test.db'

    @classmethod
    def setUpClass(cls):
        '''copy original database'''
        shutil.copyfile(master_name, cls.test_name)

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


class ConstraintsTest(unittest.TestCase):
    '''tests the table constraints and triggers defined on the schema'''

    test_name = 'test.db'

    def setUp(self):
        '''copy original database, and open connection, create cursor'''
        shutil.copyfile(master_name, self.__class__.test_name)
        self._conn = sqlite3.connect(self.__class__.test_name)
        self._conn.row_factory = sqlite3.Row
        self._cursor = self._conn.cursor()

    def tearDown(self):
        '''close database connection and remove test database'''
        self._conn.close()
        os.remove(self.__class__.test_name)

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

    def test_project_name_uniqueness(self):
        '''inserting a project with a name that is already in the table
           should fail'''
        project_name = 'project 2'
        start_date = '2015-01-05'
        end_date = '2015-12-15'
        with self.assertRaises(sqlite3.IntegrityError):
            self._cursor.execute(
                '''INSERT INTO projects (project_name, start_date, end_date)
                       VALUES (?, ?, ?);''',
                (project_name, start_date, end_date)
            )

    def test_double_assignment(self):
        '''assigning a researcher to a project twice should fail'''
        project_name = 'project 1'
        first_name = 'Bob'
        with self.assertRaises(sqlite3.IntegrityError):
            self._cursor.execute(
                '''INSERT INTO staff_assignments
                       (project_id, researcher_id)
                       SELECT p.project_id AS 'project_id',
                              r.researcher_id AS 'researcher_id'
                       FROM projects AS p, researchers AS r
                       WHERE p.project_name = ? AND
                             r.first_name = ?;''',
                (project_name, first_name)
            )

    def test_researcher_delete_trigger(self):
        '''when a researcher is deleted, the staff assignments for this
           person should be deleted as well'''
        expected_nr_rows = 1
        project_name = 'project 2'
        first_name = 'Bob'
# first, assign Bob to project 2 as well
        self._cursor.execute(
            '''INSERT INTO staff_assignments
                   (project_id, researcher_id)
                   SELECT p.project_id AS 'project_id',
                          r.researcher_id AS 'researcher_id'
                   FROM projects AS p, researchers AS r
                   WHERE p.project_name = ? AND
                         r.first_name = ?;''',
            (project_name, first_name)
        )
        self._cursor.execute(
            '''DELETE FROM researchers WHERE first_name = ?;''',
            (first_name, )
        )
        self._cursor.execute(
            '''SELECT COUNT(*) FROM staff_assignments;'''
        )
        nr_rows = 0
        for row in self._cursor:
            nr_rows += 1
        self.assertEqual(expected_nr_rows, nr_rows)
        self._cursor.execute(
            '''SELECT COUNT(*) FROM project_staffing;'''
        )
        nr_rows = 0
        for row in self._cursor:
            nr_rows += 1
        self.assertEqual(expected_nr_rows, nr_rows)

    def test_project_delete_trigger(self):
        '''when a project is deleted, the staff assignments for this
           project should be deleted as well'''
        project_name = 'project 1'
        expected_staffed_projects = {'project 2'}
        self._cursor.execute(
            '''DELETE FROM projects
                   WHERE project_name = ?;''',
            (project_name, )
        )
        self._cursor.execute(
            '''SELECT p.project_name AS 'project_name'
                   FROM projects AS p, staff_assignments AS s
                   WHERE p.project_id = s.project_id;'''
        )
        staffed_projects = set()
        for row in self._cursor:
            staffed_projects.add(row['project_name'])
        self.assertSetEqual(expected_staffed_projects, staffed_projects)

    def test_sample_update_trigger(self):
        '''when a project is deleted, samples for that project should
           refer to NULL'''
        project_name = 'project 1'
        expected_nr_samples = 3
        expected_nr_null_ref_samples = 2
        self._cursor.execute(
            '''DELETE FROM projects
                   WHERE project_name = ?;''',
            (project_name, )
        )
        self._cursor.execute(
            '''SELECT COUNT(*) FROM samples
                   WHERE project_id IS NULL;'''
        )
        nr_null_ref_samples = self._cursor.fetchone()[0]
        self.assertEqual(expected_nr_null_ref_samples, nr_null_ref_samples)
        self._cursor.execute(
            '''SELECT COUNT(*) FROM samples;'''
        )
        nr_samples = self._cursor.fetchone()[0]
        self.assertEqual(expected_nr_samples, nr_samples)


if __name__ == '__main__':
    unittest.main()
