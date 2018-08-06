#!/usr/bin/env python

from argparse import ArgumentParser
from data_utils import process_data
from keras.models import load_model


if __name__ == '__main__':
    arg_parser = ArgumentParser(description='load and evalue model')
    arg_parser.add_argument('--train', help='HDF5 file with training '
                            'data')
    arg_parser.add_argument('--test', help='HDF5 file with test data')
    arg_parser.add_argument('model_file', help='HDF5 file containing '
                                               'the model')
    options = arg_parser.parse_args()
    model = load_model(options.model_file)
    if options.train:
        x_train, y_train = process_data(options.train)
        loss, accuracy = model.evaluate(x_train, y_train)
        print(f'training: loss = {loss:.4f}, accuracy = {accuracy:.4f}')
    if options.test:
        x_test, y_test = process_data(options.test)
        loss, accuracy = model.evaluate(x_test, y_test)
        print(f'test: loss = {loss:.4f}, accuracy = {accuracy:.4f}')
