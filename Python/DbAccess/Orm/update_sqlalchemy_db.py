#!/usr/bin/env python

if __name__ == '__main__':
    from argparse import ArgumentParser
    from sqlalchemy import create_engine
    from sqlalchemy.orm import sessionmaker
    from create_sqlalchemy_db import City, Base
    arg_parser = ArgumentParser(description='create tables in database')
    arg_parser.add_argument('db_name', help='name of DB to create')
    options = arg_parser.parse_args()

    engine = create_engine('sqlite:///{0}'.format(options.db_name))
    Base.metadata.bind = engine
    DBSession = sessionmaker(bind=engine)
    db_session = DBSession()
    cities = db_session.query(City).all()
    for city in cities:
        city.name = city.name.lower()
    db_session.commit()
