#!/usr/bin/env python

from argparse import ArgumentParser
from keras.layers import (Activation, Conv2D, Dense, Dropout,
                          Flatten, LeakyReLU)
from keras.models import Sequential
from keras.optimizers import Adam
import numpy as np

from data_utils import get_data
from file_utils import change_path_suffix
from history_utils import store_history


def config_model(input_shape, output_shape):
    nr_filters = 32
    nr_dense = 50
    dropout = 0.5
    nr_classes = output_shape[0]
    conv_x_size, conv_y_size = 5, 5
    model = Sequential()
    model.add(Conv2D(nr_filters, (conv_x_size, conv_y_size),
                     strides=2, padding='valid',
                     input_shape=input_shape))
    model.add(LeakyReLU(0.1))
    model.add(Dropout(dropout))
    model.add(Conv2D(nr_filters*2, (conv_x_size, conv_y_size),
                     strides=2, padding='valid'))
    model.add(LeakyReLU(0.1))
    model.add(Dropout(dropout))
    model.add(Conv2D(nr_filters*4, (conv_x_size, conv_y_size),
                     strides=2, padding='valid'))
    model.add(LeakyReLU(0.1))
    model.add(Dropout(dropout))
    model.add(Flatten())
    model.add(Dense(nr_dense))
    model.add(LeakyReLU())
    model.add(Dropout(dropout))
    model.add(Dense(nr_classes))
    model.add(Activation('relu'))
    model.compile(loss='mean_squared_error', optimizer=Adam(),
                  metrics=['accuracy'])
    return model


if __name__ == '__main__':
    arg_parser = ArgumentParser(description='train network')
    arg_parser.add_argument('--train', required=True,
                            help='HDF5 training data')
    arg_parser.add_argument('--test', required=True,
                            help='HDF5 testing data')
    arg_parser.add_argument('--epochs', type=int, default=100,
                            help='epochs for the training process')
    arg_parser.add_argument('--batch', type=int, default=64,
                            help='training batch size')
    arg_parser.add_argument('--seed', type=int, default=1234,
                            help='seed for the RNG')
    arg_parser.add_argument('file', help='HDF5 to store network')
    options = arg_parser.parse_args()
    np.random.seed(options.seed)
    (x_train, x_val, x_test,
     y_train, y_val, y_test) = get_data(options.train, options.test)
    input_shape = x_train.shape[1:]
    output_shape = y_train.shape[1:]
    model = config_model(input_shape, output_shape)
    history = model.fit(x_train, y_train, epochs=options.epochs,
                        batch_size=options.batch, verbose=0,
                        validation_data=(x_val, y_val))
    model.save(options.file)
    hist_filename = change_path_suffix(options.file, '_hist.h5')
    store_history(hist_filename, history)
    loss, accuracy = model.evaluate(x_train, y_train, verbose=0)
    print(f'training: loss = {loss:.3f}, accuracy = {accuracy:.3f}')
    loss, accuracy = model.evaluate(x_val, y_val, verbose=0)
    print(f'validation: loss = {loss:.3f}, accuracy = {accuracy:.3f}')
    loss, accuracy = model.evaluate(x_test, y_test, verbose=0)
    print(f'test: loss = {loss:.3f}, accuracy = {accuracy:.3f}')
