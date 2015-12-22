#!/usr/bin/env python

from argparse import ArgumentParser
from sqlalchemy import create_engine
import experiments

arg_parser = ArgumentParser(description='create tables in database')
arg_parser.add_argument('db_name', help='name of DB to create')
options = arg_parser.parse_args()
engine = create_engine('sqlite:///{0}'.format(options.db_name))
experiments.Base.metadata.create_all(engine)
