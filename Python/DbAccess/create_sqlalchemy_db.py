#!/usr/bin/env python

from sqlalchemy import (Column, ForeignKey, UniqueConstraint,
                        Integer, String, DateTime, Float)
from sqlalchemy.ext.declarative import declarative_base
from sqlalchemy.orm import relationship

Base = declarative_base()


class City(Base):
    __tablename__ = 'cities'
    city_id = Column(Integer, primary_key=True)
    name = Column(String(100), nullable=False, unique=True)

    def __str__(self):
        return self.name


class Measurement(Base):
    __tablename__ = 'measurements'
    __table_args__ = (
        UniqueConstraint('time', 'city_id'),
    )
    measurement_id = Column(Integer, primary_key=True)
    time = Column(DateTime, nullable=False)
    temperature = Column(Float, nullable=False)
    city_id = Column(Integer, ForeignKey('cities.city_id'))
    city = relationship(City)

    def __str__(self):
        fmt_str = '{city:s}: {time:s}\n\tT = {temp:.1f} Celsius'
        return fmt_str.format(city=str(self.city),
                              time=str(self.time),
                              temp=self.temperature)


if __name__ == '__main__':
    from argparse import ArgumentParser
    arg_parser = ArgumentParser(description='create tables in database')
    arg_parser.add_argument('db_name', help='name of DB to create')
    options = arg_parser.parse_args()
    from sqlalchemy import create_engine
    engine = create_engine('sqlite:///{0}'.format(options.db_name))
    Base.metadata.create_all(engine)
