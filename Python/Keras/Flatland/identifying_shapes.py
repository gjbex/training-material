#!/usr/bin/env python

from argparse import ArgumentParser
import h5py
from keras import backend as K
from keras.layers import (Activation, Conv2D, Dense, Dropout,
                          Flatten, LeakyReLU)
from keras.models import Sequential
from keras.optimizers import Adam
import numpy as np
from sklearn.model_selection import train_test_split


def compute_input_shape(x_train):
    img_channels = 1
    img_rows, img_cols = x_train.shape[1], x_train.shape[2]
    if K.image_data_format() == 'channels_first':
        return (img_channels, img_rows, img_cols)
    else:  # channel_last
        return (img_rows, img_cols, img_channels)


def get_data(training_file, test_file):
    with h5py.File(training_file, 'r') as h5_file:
        x_train = np.array(h5_file['x_values'])
        y_train = np.array(h5_file['y_values'])
    with h5py.File(test_file, 'r') as h5_file:
        x_test = np.array(h5_file['x_values'])
        y_test = np.array(h5_file['y_values'])

    shape_ord = compute_input_shape(x_train)

    x_train = x_train.reshape((x_train.shape[0], ) + shape_ord)
    x_test = x_test.reshape((x_test.shape[0], ) + shape_ord)
    x_train = x_train.astype(np.float32)/255.0
    x_test = x_test.astype(np.float32)/255.0

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
    model.add(Activation('softmax'))
    model.compile(loss='categorical_crossentropy', optimizer=Adam(),
                  metrics=['accuracy'])
    return model


if __name__ == '__main__':
    arg_parser = ArgumentParser(description='train network')
    arg_parser.add_argument('--train', help='HDF5 training data')
    arg_parser.add_argument('--test', help='HDF5 testing data')
    arg_parser.add_argument('file', help='HDF5 to store network')
    options = arg_parser.parse_args()
    (x_train, x_val, x_test,
     y_train, y_val, y_test) = get_data(options.train, options.test)
    input_shape = x_train.shape[1:]
    output_shape = y_train.shape[1:]
    model = config_model(input_shape, output_shape)
    history = model.fit(x_train, y_train, epochs=100, batch_size=64,
                        validation_data=(x_val, y_val), verbose=0)
    loss, accuracy = model.evaluate(x_test, y_test, verbose=0)
    print(f'loss = {loss:.3f}, accuracy = {accuracy:.3f}')
    model.save(options.file)
