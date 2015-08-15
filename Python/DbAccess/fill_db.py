#!/usr/bin/env python

from argparse import ArgumentParser
from datetime import date, timedelta
import random
import sqlite3
import string


def generate_city_codes(nr_cities, code_length=4):
    cities = []
    for city_nr in range(nr_cities):
        cities.append(''.join([random.choice(string.letters)
                               for i in range(code_length)]))
    return cities


def convert_date(date_str):
    (year, month, day) = date_str.split('-')
    return date(int(year), int(month), int(day))


def date_xrange(start_str, end_str):
    start_date = convert_date(start_str)
    end_date = convert_date(end_str)
    delta = timedelta(days=1)
    curr_date = start_date
    while curr_date <= end_date:
        yield curr_date
        curr_date += delta


def generate_data(nr_cities, start_str, end_str):
    city_codes = generate_city_codes(nr_cities=nr_cities)
    for curr_date in date_xrange(start_str, end_str):
        for city_code in city_codes:
            yield (city_code, curr_date, random.gauss(10.0, 15.0))


def main():
    arg_parser = ArgumentParser(description='Randomly generate Sqlite '
                                            'database with weather data')
    arg_parser.add_argument('--nr_cities', action='store', type=int,
                            default=3, help='number of cities')
    arg_parser.add_argument('--start', action='store', default='2012-01-01',
                            help='date to start weather data')
    arg_parser.add_argument('--end', action='store', default='2012-01-31',
                            help='date to end weather data')
    arg_parser.add_argument('--db', action='store', required=True,
                            help='name of the database to use')
    options = arg_parser.parse_args()
    conn = sqlite3.connect(options.db)
    cursor = conn.cursor()
    cursor.execute('''CREATE TABLE IF NOT EXISTS weather (
                          city_code   TEXT NOT NULL,
                          date        TEXT NOT NULL,
                          temperature REAL NOT NULL)''')
    for data in generate_data(options.nr_cities, options.start,
                              options.end):
        cursor.execute('''INSERT INTO weather
                              (city_code, date, temperature)
                              VALUES (?, ?, ?)''',
                       data)
        print('inserted {0}, {1}, {2}'.format(data[0], data[1], data[2]))
    conn.commit()
    cursor.close()
    conn.close()

if __name__ == '__main__':
    main()
