'''Module that defines classes to describe experiments, reseachers and
   samples.  Experiments can have multple researchers associated to them,
   and vice versa.  Samples are assigned to experiments, but a sample can
   be used in a single experiment only.  Object Relational Mapping is
   provided via SQLAlchemy.'''

from sqlalchemy import (Column, ForeignKey, UniqueConstraint,
                        Integer, String, DateTime, Table)
from sqlalchemy.ext.declarative import declarative_base
from sqlalchemy.orm import relationship, backref

# Base class for all classes associated with tables in the database
Base = declarative_base()

# Table to hold the experiments-researchers many-to-many association
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
    '''An experiment have a description, a start date, and when finished,
       an end date'''
    __tablename__ = 'experiments'
    experiment_id = Column(Integer, primary_key=True)
    start_date = Column(DateTime, nullable=False)
    end_date = Column(DateTime)
    description = Column(String(2048), nullable=False)
    researchers = relationship('Researcher', secondary=staff_assignments,
                               backref='experiments')

    def __str__(self):
        '''string representation of an experiment'''
        fmt_str = 'id {id:d}: {desc:s},\n\tstarted on {start}'
        str_repr = fmt_str.format(id=self.experiment_id,
                                  desc=self.description,
                                  start=self.start_date)
        if self.end_date:
            str_repr = '{base:s}, ended on {end}'.format(base=str_repr,
                                                         end=self.end_date)
        return str_repr


class Researcher(Base):
    '''A researcher has a first name, a last name, and optionally, a
       u-number, and description'''
    __tablename__ = 'researchers'
    researcher_id = Column(Integer, primary_key=True)
    u_number = Column(String(20))
    first_name = Column(String(20), nullable=False)
    last_name = Column(String(20), nullable=False)
    description = Column(String(20))

    def __str__(self):
        '''string representation of a researcher'''
        fmt_str = 'id {id:d}: {last:s}, {first:s}'
        str_repr = fmt_str.format(id=self.researcher_id,
                                  last=self.last_name,
                                  first=self.first_name)
        if self.u_number:
            str_repr = '{base} ({u_nr})'.format(base=str_repr,
                                                u_nr=self.u_number)
        if self.description:
            str_repr = '{base}: {descr}'.format(base=str_repr,
                                                descr=self.description)

        return str_repr


class Sample(Base):
    '''A sample is associated to an experiment through the latter's ID,
       and it has a description'''
    __tablename__ = 'samples'
    sample_id = Column(Integer, primary_key=True)
    experiment_id = Column(Integer, ForeignKey('experiments.experiment_id'))
    description = Column(String, nullable=False)
    experiment = relationship('Experiment', backref=backref('samples'))

    def __str__(self):
        '''string representation of a sample'''
        fmt_str = 'id {id:d}: {descr}'
        str_repr = fmt_str.format(id=self.sample_id, descr=self.description)
        if self.experiment_id:
            str_repr = '{base} used in {e_id:d}'.format(base=str_repr,
                                                        e_id=self.experiment_id)
        return str_repr
