#!/usr/bin/env python


if __name__ == '__main__':
    from argparse import ArgumentParser
    from experiments import Experiment, Researcher, Sample
    from orm_utils import create_session
    arg_parser = ArgumentParser(description='show experiments, researchrs, '
                                            'samples in the database')
    arg_parser.add_argument('db_name', help='name of DB to create')
    options = arg_parser.parse_args()
    db_session = create_session(options.db_name)
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
