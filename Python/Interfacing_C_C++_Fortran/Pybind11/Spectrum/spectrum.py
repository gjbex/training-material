#!/usr/bin/env python

import numpy as np
from spectrum import Spectrum

spectrum = np.array(Spectrum(10))
for value in spectrum:
    print(value)
