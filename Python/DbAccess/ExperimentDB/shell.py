#!/usr/bin/env python

from argparse import ArgumentParser
import cmd
from datetime import datetime
import shlex
import sys
from sqlalchemy.orm.exc import NoResultFound
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
        if len(args) not in [1, 3]:
            msg = 'Expecting show <table> [ for <id> ]'
            raise SyntaxException(msg)
        cls_str = args[0]
        if cls_str not in classes:
            msg = "Illegal keyword '{0}' for show".format(cls_str)
            raise SyntaxException(msg)
        cls = classes[cls_str]
        if len(args) > 1 and args[1] != 'for':
            msg = "Syntax error, expected for, not '{0}'".format(args[1])
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
        elif cls == Experiment:
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
        if args[0] == 'experiment':
            try:
                args[2] = datetime.strptime(args[2], '%Y-%m-%d %H:%M:%S')
            except:
                msg = "timestamp should be yyyy-mm-dd HH:MM:SS, not '{0]}"
                raise SyntaxException(msg.format(args[2]))
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
        args = shlex.split(arg_str)
        if len(args) != 3:
            msg = 'Expecting assign <id> to <id>'
            raise SyntaxException(msg)
        if args[1] != 'to':
            msg = "Syntax error, expected to, not '{0}'".format(args[1])
            raise SyntaxException(msg)
        try:
            args[0] = int(args[0])
        except:
            msg = "researcher ID must be int, not '{0]}".format(args[0])
            raise SyntaxException(msg)
        try:
            args[2] = int(args[2])
        except:
            msg = "experiment ID must be int, not '{0]}".format(args[2])
            raise SyntaxException(msg)
        return args[0], args[2]

    def do_assign(self, arg_str):
        '''Use: assign <researcher_id> to <experiment_id>'''

        try:
            r_id, e_id = ExperimentShell.parse_assign_arg(arg_str)
        except SyntaxException as e:
            print('*** {0}'.format(str(e)), file=sys.stderr)
            return
        try:
            experiment = self._db_session.\
                              query(Experiment).\
                              filter_by(experiment_id=e_id).one()
        except NoResultFound:
            print('*** No experiment with ID {0:d}'.format(e_id),
                  file=sys.stderr)
            return
        try:
            researcher = self._db_session.\
                              query(Researcher).\
                              filter_by(researcher_id=r_id).one()
        except NoResultFound:
            print('*** No researcher with ID {0:d}'.format(r_id),
                  file=sys.stderr)
            return
        experiment.researchers.append(researcher)
        self._db_session.commit()

    @staticmethod
    def parse_set_arg(arg_str):
        args = shlex.split(arg_str)
        attrs = {
            'end_date': Experiment,
            'description': Researcher,
            'u_number': Researcher,
        }
        if len(args) != 4:
            msg = 'Expecting set <attr> to <value>'
            raise SyntaxException(msg)
        if args[0] not in attrs:
            msg = "Illegal keyword '{0}' for set".format(args[0])
            raise SyntaxException(msg)
        if args[2] != 'for':
            msg = "Syntax error, expected for, not '{0}'".format(args[2])
            raise SyntaxException(msg)
        if args[0] == 'end_date':
            try:
                args[1] = datetime.strptime(args[1], '%Y-%m-%d %H:%M:%S')
            except:
                msg = "timestamp should be yyyy-mm-dd HH:MM:SS, not '{0]}"
                raise SyntaxException(msg.format(args[1]))
        try:
            args[3] = int(args[3])
        except:
            msg = "ID must be int, not '{0]}".format(args[3])
            raise SyntaxException(msg)
        return attrs[args[0]], args[0], args[1], args[3]

    def do_set(self, arg_str):
        '''Use either:
           set end_date <datetime> for <experiment_id>
           set description <string> for <researcher_id>
           set u_number <id> for <reseacer_id>'''
        try:
            cls, attr, val, item_id = ExperimentShell.parse_set_arg(arg_str)
        except SyntaxException as e:
            print('*** {0}'.format(str(e)), file=sys.stderr)
            return
        if cls == Experiment:
            try:
                experiment = self._db_session.\
                                  query(Experiment).\
                                  filter_by(experiment_id=item_id).one()
                experiment.end_date = val
                self._db_session.commit()
            except NoResultFound:
                print('*** No experiment with ID {0:d}'.format(item_id),
                      file=sys.stderr)
                return
        elif cls == Researcher:
            try:
                researcher = self._db_session.\
                                  query(Researcher).\
                                  filter_by(researcher_id=item_id).one()
            except NoResultFound:
                print('*** No researcher with ID {0:d}'.format(item_id),
                      file=sys.stderr)
                return
            if attr == 'description':
                researcher.description = val
            elif attr == 'u_number':
                researcher.u_number = val
            self._db_session.commit()

    @staticmethod
    def parse_remove_arg(arg_str):
        classes = {
            'experiment': Experiment,
            'researcher': Researcher,
            'sample': Sample,
        }
        args = shlex.split(arg_str)
        if len(args) != 2:
            msg = 'Expecting remove <type> <id>'
            raise SyntaxException(msg)
        if args[0] not in classes:
            msg = "Illegal keyword '{0}' for remove".format(args[0])
            raise SyntaxException(msg)
        try:
            args[1] = int(args[1])
        except:
            msg = "ID must be int, not '{0]}".format(args[1])
            raise SyntaxException(msg)
        return classes[args[0]], args[1]

    def do_remove(self, arg_str):
        '''User either:
           remove experiment <experiment_id>
           remove researcher <researcher_id>
           remove sample <sample_id>'''
        try:
            cls, item_id = ExperimentShell.parse_remove_arg(arg_str)
        except SyntaxException as e:
            print('*** {0}'.format(str(e)), file=sys.stderr)
            return
        if cls == Experiment:
            try:
                experiment = self._db_session.\
                                  query(Experiment).\
                                  filter_by(experiment_id=item_id).one()
                self._db_session.delete(experiment)
            except NoResultFound:
                print('*** No experiment with ID {0:d}'.format(item_id),
                      file=sys.stderr)
                return
        elif cls == Researcher:
            try:
                researcher = self._db_session.\
                                  query(Researcher).\
                                  filter_by(researcher_id=item_id).one()
                self._db_session.delete(researcher)
            except NoResultFound:
                print('*** No researcher with ID {0:d}'.format(item_id),
                      file=sys.stderr)
                return
        elif cls == Sample:
            try:
                sample = self._db_session.\
                                  query(Sample).\
                                  filter_by(sample_id=item_id).one()
                self._db_session.delete(sample)
            except NoResultFound:
                print('*** No sample with ID {0:d}'.format(item_id),
                      file=sys.stderr)
                return
        self._db_session.commit()


if __name__ == '__main__':
    arg_parser = ArgumentParser(description='shell for database '
                                            'interaction')
    arg_parser.add_argument('db_name', help='name of the database to use')
    options = arg_parser.parse_args()
    ExperimentShell(options.db_name).cmdloop()
