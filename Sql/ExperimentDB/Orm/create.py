#!/usr/bin/env python

from sqlalchemy import (Column, ForeignKey, UniqueConstraint,
                        Integer, String, DateTime, Table)
from sqlalchemy.ext.declarative import declarative_base
from sqlalchemy.orm import relationship, backref

Base = declarative_base()

staff_assignments = Table(
    'staff_assignments', Base.metadata, Column(
        'experiment_id',
        Integer,
        ForeignKey('experiments.experiment_id')
    ),
    Column(
        'researcher_id',
        Integer,
        ForeignKey('researchers.researcher_id')
    ),
    UniqueConstraint('experiment_id', 'researcher_id')
)


class Experiment(Base):
    __tablename__ = 'experiments'
    experiment_id = Column(Integer, primary_key=True)
    start_date = Column(DateTime, nullable=False)
    end_date = Column(DateTime)
    description = Column(String(2048), nullable=False)
    researchers = relationship('Researcher', secondary=staff_assignments,
                               backref='experiments')

    def __str__(self):
        fmt_str = 'id {id:d}: {desc:s}'
        return fmt_str.format(id=self.experiment_id,
                              desc=self.description)


class Researcher(Base):
    __tablename__ = 'researchers'
    researcher_id = Column(Integer, primary_key=True)
    u_number = Column(String(20))
    first_name = Column(String(20), nullable=False)
    last_name = Column(String(20), nullable=False)
    description = Column(String(20))

    def __str__(self):
        fmt_str = 'id {id:d}: {last:s}, {first:s}'
        return fmt_str.format(id=self.researcher_id,
                              last=self.last_name,
                              first=self.first_name)


class Sample(Base):
    __tablename__ = 'samples'
    sample_id = Column(Integer, primary_key=True)
    experiment_id = Column(Integer, ForeignKey('experiments.experiment_id'))
    description = Column(String, nullable=False)
    experiment = relationship('Experiment', backref=backref('samples'))

    def __str__(self):
        fmt_str = 'id {id:d}: {descr}'
        return fmt_str.format(id=self.sample_id, descr=self.description)


if __name__ == '__main__':
    from argparse import ArgumentParser
    arg_parser = ArgumentParser(description='create tables in database')
    arg_parser.add_argument('db_name', help='name of DB to create')
    options = arg_parser.parse_args()
    from sqlalchemy import create_engine
    engine = create_engine('sqlite:///{0}'.format(options.db_name))
    Base.metadata.create_all(engine)
