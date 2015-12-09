#!/usr/bin/env python


def convert2date(date_str):
    year, month, day = list(map(int, date_str.split('-')))
    return datetime(year, month, day)

if __name__ == '__main__':
    from argparse import ArgumentParser
    from datetime import datetime
    from sqlalchemy import create_engine
    from sqlalchemy.orm import sessionmaker
    from create import Experiment, Researcher, Sample, Base
    arg_parser = ArgumentParser(description='create tables in database')
    arg_parser.add_argument('db_name', help='name of DB to create')
    options = arg_parser.parse_args()

    engine = create_engine('sqlite:///{0}'.format(options.db_name))
    Base.metadata.bind = engine
    DBSession = sessionmaker(bind=engine)
    db_session = DBSession()
    experiments = db_session.query(Experiment).all()
    for experiment in experiments:
        print(experiment.description)
        for researcher in experiment.researchers:
            print('\t{0}, {1}'.format(researcher.last_name,
                                      researcher.first_name))
        for sample in experiment.samples:
            print('\t{}'.format(sample.description))
    samples = db_session.query(Sample).all()
    for sample in samples:
        print(sample.description)
        print('\t{0}'.format(sample.experiment.description))
    researchers = db_session.query(Researcher).all()
    for researcher in researchers:
        print(researcher)
        for experiment in researcher.experiments:
            print('\t{}'.format(experiment.description))
