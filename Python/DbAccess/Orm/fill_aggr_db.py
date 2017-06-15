#!/usr/bin/env python

if __name__ == '__main__':
    from argparse import ArgumentParser
    from sqlalchemy import create_engine
    from sqlalchemy.orm import sessionmaker
    from sqlalchemy.sql import func
    from create_sqlalchemy_db import (Base as OrigBase, City as OrigCity,
                                      Measurement as OrigMeasurement)
    from create_aggr_db import (Base as AggrBase, City as AggrCity,
                                AggrMeasurement)
    arg_parser = ArgumentParser(description='create tables in database')
    arg_parser.add_argument('-orig_db', help='database with original data')
    arg_parser.add_argument('-aggr_db', help='database with aggregate data')
    options = arg_parser.parse_args()
    orig_engine = create_engine('sqlite:///{0}'.format(options.orig_db))
    aggr_engine = create_engine('sqlite:///{0}'.format(options.aggr_db))
    OrigDBSession = sessionmaker(bind=orig_engine)
    AggrDBSession = sessionmaker(bind=aggr_engine)
    orig_db_session = OrigDBSession()
    aggr_db_session = AggrDBSession()
    results = orig_db_session \
        .query(func.avg(OrigMeasurement.temperature), OrigCity) \
        .group_by(OrigCity.name) \
        .all()
    for result in results:
        measurement = AggrMeasurement(avg_temp=result[0],
                                      city=AggrCity.copy(result[1]))
        aggr_db_session.add(measurement)
    aggr_db_session.commit()
