from sklearn.model_selection import train_test_split
from sklearn.pipeline import Pipeline
from sklearn.preprocessing import FunctionTransformer, OneHotEncoder
import matplotlib.pyplot as plt
import numpy as np


def create_input_pipeline():
    input_reshaper = FunctionTransformer(lambda x: x.reshape(x.shape[0], -1),
                                         validate=False)
    input_normalizer = FunctionTransformer(lambda x: x.astype(np.float32)/255.0,
                                           validate=True)
    return Pipeline([
        ('reshaper', input_reshaper),
        ('normalizer', input_normalizer),
    ])


def create_output_pipeline():
    output_reshaper = FunctionTransformer(lambda x: x.reshape(-1, 1),
                                          validate=False)
    output_encoder = OneHotEncoder(categories='auto')
    output_type_changer = FunctionTransformer(lambda x: x.astype(np.float32),
                                              validate=False)
    return Pipeline([
        ('reshaper', output_reshaper),
        ('binarizer', output_encoder),
        ('type_changer', output_type_changer),
    ])


def plot_history(network_history):
    plt.figure()
    plt.xlabel('Epochs')
    plt.ylabel('Loss')
    plt.plot(network_history.history['loss'])
    plt.plot(network_history.history['val_loss'])
    plt.legend(['Training', 'Validation'])
    plt.figure()
    plt.xlabel('Epochs')
    plt.ylabel('Accuracy')
    plt.plot(network_history.history['acc'])
    plt.plot(network_history.history['val_acc'])
    plt.legend(['Training', 'Validation'], loc='lower right')


def plot_confusion_matrix(cm, classes,
                      normalize=False,
                      cmap=plt.cm.Blues):
    log1p_cm = np.log1p(cm)
    if normalize:
        cm = cm.astype(np.float)/cm.sum(axis=1)[:, np.newaxis]
    figure, axes = plt.subplots(figsize=(6, 6))
    axes.imshow(log1p_cm, interpolation='nearest', cmap=cmap)
    axes.set_xticks(classes)
    axes.set_yticks(classes)
    fmt = '{0:.4f}' if normalize else '{0:d}'
    thresh = 0.5*cm.max()
    for i, j in itertools.product(range(cm.shape[0]), range(cm.shape[1])):
        axes.text(j, i, fmt.format(cm[i, j]),
                  horizontalalignment="center",
                  color="white" if cm[i, j] > thresh else "black",
                  fontsize=8)
    figure.tight_layout()
    axes.set_ylabel('True label')
    axes.set_xlabel('Predicted label')