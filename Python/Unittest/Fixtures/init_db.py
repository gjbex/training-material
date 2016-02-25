#!/usr/bin/env python

from argparse import ArgumentParser
import sqlite3
import sys


def execute_statement(cursor, sql_statement, is_verbose=False):
    '''execute SQL statement if it is non-empty'''
    if len(sql_statement):
        if is_verbose:
            print('executing:\n{0}'.format(sql_statement), file=sys.stderr)
        cursor.execute(sql_statement)


def execute_file(conn, file_name, is_verbose=False):
    '''execute all SQL statements in the specified file, statements are
       expected to be separated by SQL comments, i.e., '--' '''
    if is_verbose:
        print('processing {0}'.format(file_name), file=sys.stderr)
    cursor = conn.cursor()
    with open(file_name, 'r') as sql_file:
        sql_statement = ''
        for line in sql_file:
            if line.lstrip().startswith('--'):
                execute_statement(cursor, sql_statement, is_verbose)
                sql_statement = ''
            else:
                sql_statement += line
        execute_statement(cursor, sql_statement, is_verbose)
    conn.commit()


if __name__ == '__main__':
    arg_parser = ArgumentParser(description='create and initialize an '
                                            'Sqlite3 database',
                                epilog='note: in SQL files, statements '
                                       'must be separated by comments')
    arg_parser.add_argument('db', help='name of the database file to be '
                                       'created')
    arg_parser.add_argument('--create', required=True,
                            help='file with SQL statements to create the '
                                 'database')
    arg_parser.add_argument('--fill', nargs='*', default=[],
                            help='file(s) with SQL statements to insert '
                                 'values into the database')
    arg_parser.add_argument('--verbose', action='store_true',
                            help='show SQL statements that will be '
                                 'executed')
    options = arg_parser.parse_args()
    conn = sqlite3.connect(options.db)
    execute_file(conn, options.create, options.verbose)
    for file_name in options.fill:
        execute_file(conn, file_name, options.verbose)
    conn.close()
