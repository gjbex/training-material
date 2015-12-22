'''Module with some convenient function for ORM usage'''

from sqlalchemy import create_engine
from sqlalchemy.orm import sessionmaker
from experiments import Base


def create_session(db_name):
    '''Create a SQLAlchemy database session based on the provided name'''
    engine = create_engine('sqlite:///{0}'.format(db_name))
    Base.metadata.bind = engine
    DBSession = sessionmaker(bind=engine)
    return DBSession()
