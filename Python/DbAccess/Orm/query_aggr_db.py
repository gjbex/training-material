#!/usr/bin/env python

if __name__ == '__main__':
    from argparse import ArgumentParser
    from sqlalchemy import create_engine
    from sqlalchemy.orm import sessionmaker
    from sqlalchemy.sql import func
    from create_aggr_db import (Base as AggrBase, City as AggrCity,
                                AggrMeasurement)
    arg_parser = ArgumentParser(description='create tables in database')
    arg_parser.add_argument('aggr_db', help='database with aggregate data')
    options = arg_parser.parse_args()
    aggr_engine = create_engine('sqlite:///{0}'.format(options.aggr_db))
    AggrDBSession = sessionmaker(bind=aggr_engine)
    aggr_db_session = AggrDBSession()
    results = aggr_db_session.query(AggrMeasurement).all()
    for result in results:
        print("{0}: {1:.2f}".format(result.city.name, result.avg_temp))
