import h5py
import matplotlib.pyplot as plt
import numpy as np


def store_history(file_name, history):
    '''Function to store the model training history into an HDF5 file

    file_name: name for the HDF5 file
    history: history to store
    '''
    with h5py.File(file_name, 'w') as h5_file:
        for key, values in history.history.items():
            h5_file[key] = np.array(values)


def plot_history_data(loss, val_loss, acc, val_acc):
    _, axes = plt.subplots(nrows=1, ncols=2, figsize=(12, 6))
    axes[0].set_xlabel('Epochs')
    axes[0].set_ylabel('Loss')
    axes[0].plot(loss)
    axes[0].plot(val_loss)
    axes[0].legend(['Training', 'Validation'])

    axes[1].set_xlabel('Epochs')
    axes[1].set_ylabel('Accuracy')
    axes[1].plot(acc)
    axes[1].plot(val_acc)
    axes[1].legend(['Training', 'Validation'], loc='lower right')


def plot_history(history):
    plot_history_data(history.history['loss'],
                      history.history['val_loss'],
                      history.history['acc'],
                      history.history['val_acc'])


def plot_history_file(history_filename):
    with h5py.File(history_filename, 'r') as hist_file:
        loss = hist_file['loss']
        acc = hist_file['acc']
        val_loss = hist_file['val_loss']
        val_acc = hist_file['val_acc']
        plot_history_data(loss, val_loss, acc, val_acc)
