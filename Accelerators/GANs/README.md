# GANs
Implementation of a Generative Adversary Network for MNIST data using
TensorFlow.

## What is it?
* `gan.py`: TensorFlow implementation of the GAN for MNIST data.
* `gan_cpu.pbs`: PBS script to run on a compute node without GPUs.
* `gan_gpu.pbs`: PBS script to run on a compute node with GPUs.

## Results
The CPU-only run took 2,508 seconds (2,508 seconds (dual socket Intel(R)
Xeon(R) CPU E5-2680 v2 @ 2.80GHz.
The GPU run took 978 seconds (NVIDIA K40c).

The speedup of GPU versus CPU is 2.6.
