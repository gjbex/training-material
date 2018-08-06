import h5py
from keras import backend as K
import numpy as np
from sklearn.model_selection import train_test_split


def compute_input_shape(x_train):
    '''Compute the sahpe of the grayscale input. The color
    channels should be eitehr first, or last, depending on
    the keras backend beining used.

    x_train: numpy array nr_examples x width x height
    output: numpy array with color channel added
    '''
    img_channels = 1
    img_rows, img_cols = x_train.shape[1], x_train.shape[2]
    if K.image_data_format() == 'channels_first':
        return (img_channels, img_rows, img_cols)
    else:  # channel_last
        return (img_rows, img_cols, img_channels)


def process_data(data_file):
    '''Read an HDF5 file containing a data set, both input and
    output, and preprocess.

    data_file: name of the file containing the data

    ouptut: tuple of input data, output data
    '''
    with h5py.File(data_file, 'r') as h5_file:
        x_data = np.array(h5_file['x_values'])
        y_data = np.array(h5_file['y_values'])
    shape_ord = compute_input_shape(x_data)
    x_data = x_data.reshape((x_data.shape[0], ) + shape_ord)
    x_data = x_data.astype(np.float32)/255.0
    return x_data, y_data


def get_data(training_file, test_file, seed=1234):
    '''Read the training and test data, preprocess, and split
    the training data into actual training and validation set.

    training_file: file name of the trainig data
    test_file: file name of the test data

    output: 6-tuple of training, validation and test input,
            training, validation and test output
    '''
    x_train, y_train = process_data(training_file)
    x_test, y_test = process_data(test_file)
    np.random.seed(seed)
    x_train, x_val, y_train, y_val = train_test_split(x_train, y_train)
    return x_train, x_val, x_test, y_train, y_val, y_test
