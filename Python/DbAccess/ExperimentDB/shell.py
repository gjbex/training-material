#!/usr/bin/env python

from argparse import ArgumentParser
import cmd
import sys
from experiments import Experiment, Researcher, Sample
from orm_utils import create_session


class ExperimentShell(cmd.Cmd):
    '''Shell to interact with the experiment database'''
    intro = 'Welcome to the ExperimentShell, type help to list commands'
    prompt = 'exp-db> '

    def __init__(self, db_name):
        super().__init__()
        self._db_session = create_session(db_name)

    def do_quit(self, arg_str):
        '''quit the shell'''
        return True

    def do_show(self, arg_str):
        '''show either projects, researchers or samples'''
        if arg_str == 'projects':
            for experiment in self._db_session.query(Experiment).all():
                print(experiment)
        elif arg_str == 'researchers':
            for researcher in self._db_session.query(Researcher).all():
                print(researcher)
        elif arg_str == 'samples':
            for sample in self._db_session.query(Sample).all():
                print(sample)
        else:
            print("illegal keyword '{0}' for show".format(arg_str),
                  file=sys.stderr)


if __name__ == '__main__':
    arg_parser = ArgumentParser(description='shell for database '
                                            'interaction')
    arg_parser.add_argument('db_name', help='name of the database to use')
    options = arg_parser.parse_args()
    ExperimentShell(options.db_name).cmdloop()
