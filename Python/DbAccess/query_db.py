#!/usr/bin/env python

from argparse import ArgumentParser
import sqlite3


def main():
    arg_parser = ArgumentParser(description='Compute average temperatures')
    arg_parser.add_argument('--start', action='store', default='2012-01-01',
                            help='date to start weather data')
    arg_parser.add_argument('--end', action='store', default='2012-01-31',
                            help='date to end weather data')
    arg_parser.add_argument('--db', action='store', required=True,
                            help='name of the database to use')
    options = arg_parser.parse_args()
    conn = sqlite3.connect(options.db)
    conn.row_factory = sqlite3.Row
    cursor = conn.cursor()
    cursor.execute('''SELECT city_code,
                             AVG(temperature) AS 'temperature'
                          FROM weather
                          WHERE date BETWEEN ? AND ?
                          GROUP BY city_code''',
                   (options.start, options.end))
    for row in cursor:
        print('{city}\t{tmp}'.format(city=row['city_code'],
                                     tmp=row['temperature']))
    cursor.close()

if __name__ == '__main__':
    main()
