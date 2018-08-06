#!/usr/bin/env python

from argparse import ArgumentParser
import h5py
from keras import backend as K
from keras.layers import (Activation, Conv2D, Dense, Dropout,
                          Flatten, LeakyReLU)
from keras.models import Sequential
from keras.optimizers import Adam
import numpy as np
from pathlib import Path
import pickle
from sklearn.model_selection import train_test_split


def compute_input_shape(x_train):
    img_channels = 1
    img_rows, img_cols = x_train.shape[1], x_train.shape[2]
    if K.image_data_format() == 'channels_first':
        return (img_channels, img_rows, img_cols)
    else:  # channel_last
        return (img_rows, img_cols, img_channels)


def process_data(data_file):
    with h5py.File(data_file, 'r') as h5_file:
        x_data = np.array(h5_file['x_values'])
        y_data = np.array(h5_file['y_values'])
    shape_ord = compute_input_shape(x_data)
    x_data = x_data.reshape((x_data.shape[0], ) + shape_ord)
    x_data = x_data.astype(np.float32)/255.0
    return x_data, y_data


def get_data(training_file, test_file):
    x_train, y_train = process_data(training_file)
    x_test, y_test = process_data(test_file)
    np.random.seed(1234)
    x_train, x_val, y_train, y_val = train_test_split(x_train, y_train)
    return x_train, x_val, x_test, y_train, y_val, y_test


def config_model(input_shape, output_shape):
    nr_filters = 32
    nr_classes = output_shape[0]
    conv_x_size, conv_y_size = 5, 5
    model = Sequential()
    model.add(Conv2D(nr_filters, (conv_x_size, conv_y_size),
                     strides=2, padding='valid',
                     input_shape=input_shape))
    model.add(LeakyReLU(0.1))
    model.add(Dropout(0.4))
    model.add(Conv2D(nr_filters*2, (conv_x_size, conv_y_size), strides=2,
                     padding='valid'))
    model.add(LeakyReLU(0.1))
    model.add(Dropout(0.4))
    model.add(Conv2D(nr_filters*4, (conv_x_size, conv_y_size), strides=2,
                     padding='valid'))
    model.add(LeakyReLU(0.1))
    model.add(Dropout(0.4))
    model.add(Flatten())
    model.add(Dense(nr_classes))
    model.add(Activation('relu'))
    model.compile(loss='mean_squared_error', optimizer=Adam(),
                  metrics=['accuracy'])
    return model


def change_path_suffix(path_str, suffix_str):
    path = Path(path_str)
    dir_path = path.parent
    file_base = path.stem
    return str(dir_path / (file_base + suffix_str))


if __name__ == '__main__':
    arg_parser = ArgumentParser(description='train network')
    arg_parser.add_argument('--train', required=True,
                            help='HDF5 training data')
    arg_parser.add_argument('--test', required=True,
                            help='HDF5 testing data')
    arg_parser.add_argument('--epochs', type=int, default=100,
                            help='epochs for the training process')
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
    history = model.fit(x_train, y_train, epochs=options.epochs, batch_size=64,
                        validation_data=(x_val, y_val), verbose=0)
    model.save(options.file)
    hist_filename = change_path_suffix(options.file, '_hist.pkl')
    with open(hist_filename, 'wb') as hist_file:
        pickle.dump(hist_file, history)
    loss, accuracy = model.evaluate(x_train, y_train, verbose=0)
    print(f'training: loss = {loss:.3f}, accuracy = {accuracy:.3f}')
    loss, accuracy = model.evaluate(x_val, y_val, verbose=0)
    print(f'validation: loss = {loss:.3f}, accuracy = {accuracy:.3f}')
    loss, accuracy = model.evaluate(x_test, y_test, verbose=0)
    print(f'test: loss = {loss:.3f}, accuracy = {accuracy:.3f}')
