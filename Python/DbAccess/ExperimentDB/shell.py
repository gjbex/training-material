#!/usr/bin/env python

from argparse import ArgumentParser
import cmd
import shlex
import sys
from experiments import Experiment, Researcher, Sample, staff_assignments
from orm_utils import create_session


class SyntaxException(Exception):
    pass


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

    @staticmethod
    def parse_show_arg(arg_str):
        classes = {
            'experiments': Experiment,
            'researchers': Researcher,
            'samples': Sample
        }
        args = shlex.split(arg_str)
        if len(args) != 1 and len(args) != 3:
            msg = 'Expecting show <table> [ for <id> ]'
            raise SyntaxException(msg)
        cls_str = args[0]
        if cls_str not in classes:
            msg = "Illegal keyword '{0}' for show".format(cls_str)
            raise SyntaxException(msg)
        cls = classes[cls_str]
        if len(args) > 1 and args[1] != 'for':
            msg = "Syntax error, expected for, not '{0}'".format(cls_str)
            raise SyntaxException(msg)
        if len(args) == 3:
            try:
                item_id = int(args[2])
            except:
                msg = "Syntax error, expected ID, not '{0}'".format(args[2])
                raise SyntaxException(msg)
        else:
            item_id = None
        return cls, item_id

    def do_show(self, arg_str):
        '''Use either:
           show experiments [ for <researcher_id> ]
           show researchers [ for <experiment_id> ]
           show samples [ for <experiment_id> ]'''
        try:
            cls, item_id = ExperimentShell.parse_show_arg(arg_str)
        except SyntaxException as e:
            print('*** {0}'.format(str(e)), file=sys.stderr)
            return
        if not item_id:
            items = self._db_session.query(cls).all()
        else:
            if cls == Experiment:
                items = self._db_session.\
                             query(Experiment).\
                             join(staff_assignments).\
                             filter_by(researcher_id=item_id).all()
            elif cls == Researcher:
                items = self._db_session.\
                             query(Researcher).\
                             join(staff_assignments).\
                             filter_by(experiment_id=item_id).all()
            elif cls == Sample:
                items = self._db_session.\
                             query(Sample).\
                             filter_by(experiment_id=item_id).all()
        for item in items:
            print(item)

    @staticmethod
    def parse_add_arg(arg_str):
        types = {'experiment', 'researcher', 'sample'}
        args = shlex.split(arg_str)
        if len(args) != 3:
            msg = 'Expecting add <type> <attr1> <attr2>'
            raise SyntaxException(msg)
        if args[0] not in types:
            msg = "Illegal keyword '{0}' for add".format(args[0])
            raise SyntaxException(msg)
        if args[0] == 'sample':
            try:
                args[2] = int(args[2])
            except:
                msg = "experiment ID must be int, not '{0]}".format(args[2])
                raise SyntaxException(msg)
        return args[0], args[1], args[2]

    def do_add(self, arg_str):
        '''Use either:
           add experiment <description> <start_date>
           add researcher <last_name> <first_name>
           add sample <description> <experiment_id>'''
        try:
            type_str, attr1, attr2 = ExperimentShell.parse_add_arg(arg_str)
        except SyntaxException as e:
            print('*** {0}'.format(str(e)), file=sys.stderr)
            return
        if type_str == 'experiment':
            item = Experiment(description=attr1, start_date=attr2)
        elif type_str == 'researcher':
            item = Researcher(last_name=attr1, first_name=attr2)
        elif type_str == 'sample':
            item = Sample(description=attr1, experiment_id=attr2)
        self._db_session.add(item)
        self._db_session.commit()

    @staticmethod
    def parse_assign_arg(arg_str):
        pass

    def do_assign(self, arg_str):
        '''Use: assign <researcher_id> to <experiment_id>'''
        pass


if __name__ == '__main__':
    arg_parser = ArgumentParser(description='shell for database '
                                            'interaction')
    arg_parser.add_argument('db_name', help='name of the database to use')
    options = arg_parser.parse_args()
    ExperimentShell(options.db_name).cmdloop()
