#!/usr/bin/env python

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
# create and add researchers
    nele = Researcher(first_name='Nele', last_name='Famaey')
    db_session.add(nele)
    heleen = Researcher(first_name='Heleen', last_name='Fehervary')
    db_session.add(heleen)
    db_session.commit()
# create experiments
    exp1 = Experiment(
        start_date=datetime(2015, 10, 23, 9, 11),
        end_date=datetime(2015, 10, 25, 13, 43),
        description='first experiment'
    )
    exp1.researchers.append(nele)
    exp1.samples.append(Sample(description='sample 1'))
    exp1.samples.append(Sample(description='sample 2'))
    db_session.add(exp1)
    exp2 = Experiment(
        start_date=datetime(2015, 10, 27, 9, 5),
        end_date=datetime(2015, 10, 28, 14, 53),
        description='second experiment'
    )
    exp2.researchers.append(nele)
    exp2.researchers.append(heleen)
    exp2.samples.append(Sample(description='sample 3'))
    db_session.add(exp2)
    db_session.commit()
