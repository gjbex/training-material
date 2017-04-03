#!/usr/bin/env python

from datetime import datetime


def convert2date(date_str):
    year, month, day = list(map(int, date_str.split('-')))
    return datetime(year, month, day)

if __name__ == '__main__':
    from argparse import ArgumentParser
    import sys
    from sqlalchemy import create_engine
    from sqlalchemy.orm import sessionmaker
    from create_sqlalchemy_db import City, Measurement, Base
    arg_parser = ArgumentParser(description='create tables in database')
    arg_parser.add_argument('db_name', help='name of DB to create')
    arg_parser.add_argument('-list', action='store_true',
                            help='show a list of all cities')
    arg_parser.add_argument('-city', help='city to query for')
    arg_parser.add_argument('-start', default='1980-01-01',
                            help='start date')
    arg_parser.add_argument('-end', default='2030-12-31',
                            help='end date')
    options = arg_parser.parse_args()

    engine = create_engine('sqlite:///{0}'.format(options.db_name))
    Base.metadata.bind = engine
    DBSession = sessionmaker(bind=engine)
    db_session = DBSession()
    cities = db_session.query(City).all()
    if options.list:
        for city in cities:
            print(city.name)
        sys.exit(0)
    if options.city:
        if options.city not in [city.name for city in cities]:
            msg = '### error: {0} is not in DB\n'
            sys.stderr.write(msg.format(options.city))
        start_date = convert2date(options.start)
        end_date = convert2date(options.end)
        measurements = db_session.query(Measurement) \
                                 .join('city') \
                                 .filter(City.name == options.city,
                                         start_date <= Measurement.time,
                                         Measurement.time <= end_date) \
                                 .all()
        for measurement in measurements:
            print(measurement)
