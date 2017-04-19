#!/usr/bin/env python

import matplotlib.pyplot as plt
import numpy as np
from scipy.signal import convolve2d
from skimage import color, data, restoration

if __name__ == '__main__':
    image = color.rgb2gray(data.astronaut())
    point_spread_func = np.ones((5, 5))/25.0
    image = convolve2d(image, point_spread_func, 'same')
    image += 0.1*image.std()*np.random.standard_normal(image.shape)
    denoised, _ = restoration.unsupervised_wiener(image, point_spread_func)
    figure, axes = plt.subplots(nrows=1, ncols=2, sharex=True, sharey=True,
                                subplot_kw={'adjustable': 'box-forced'},
                                figsize=(8,5))
    plt.gray()
    axes[0].imshow(image, vmin=denoised.min(), vmax=denoised.max())
    axes[0].axis('off')
    axes[0].set_title('original')
    axes[1].imshow(denoised)
    axes[1].axis('off')
    axes[1].set_title('restored')
    figure.tight_layout()
    plt.show()
