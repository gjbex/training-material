# How to install TensorFlow?
Here, we describe how to install TensorFlow using conda with support for
GPU computing.  We assume a 64-bit Linux system, with a CUDA-capable
graphics card.  We assume that Python 3.6+ is used.


## Intralling Miniconda
If you have Miniconda already installed, you can skip ahead to the next
section, if Miniconda is not installed, we start with that. Download the
Bash script that will install it from
[conda.io](https://repo.continuum.io/miniconda/Miniconda3-latest-Linux-x86_64.sh) using, e.g., `wget`:
```bash
$ wget https://repo.continuum.io/miniconda/Miniconda3-latest-Linux-x86_64.sh
```
Once downloaded, run the script:
```bash
$ bash Miniconda3-latest-Linux-x86_64.sh
```
You will be asked a number of questions.

1. First, the installer will let you have to review the
    license, press enter as requested.  The license is shown, read it,
    hitting the space bar for the next pages.  If you agree, type "yes"
    when requested.
1. The installer will suggest an installation directory, `miniconda3` in
    your home directory.  Bear in mind that, depending on the number of
    conda environments you wish to have, and the number of Python packages,
    you might be better of installing this in your `$VSC_DATA`
    directory.  So if your VSC user ID is vsc98765, and your account's
    affiliation is `my_uni` (either `antwerpen`, `brussel`, `gent`, or
    `leuven`), then the directory could be changed to
    `/data/my_uni/987/vsc98765/miniconda3`.  Typically, your home
    directory will do though.  Either press return to accept the installer's
    suggestion, or enter your own, and pressing return to proceed.
1. The installation will now proceed.
1. Next, the installer will offer to permanently add the path to the
    Miniconda installation to the `PATH` environment variable in your
    `.bashrc` file.  This is convenient, but may lead to conflicts when
    working with the module system, so make sure that you know what you
    are doing in either case.


## Creating an environment
First, ensure that the Miniconda installation is in your `PATH`.  The
following command should return the full path to the `conda` command:
```bash
$ which conda
```
If the result is blank, or reports that `conda` can not be found, modify
the `PATH` environment variable appropriately by adding Miniconda's
`bin` directory to `PATH`.

Creating a new conda environment is straightforward:
```bash
$ conda create  -n base_env  numpy scipy matplotlib pandas
```
This command creates a new conda environment called `base_env`, and
installs a number of Python packages that you will probably want to have
handy in any case to preprocess, visualize, or postprocess your data.
You can of course install more, depending on your requirements and
personal taste.


## TensorFlow with GPU support
Clone the `base_env` environment, and install the non-GPU version of
TensorFlow in it:
```bash
$ source deactivate
$ conda create  -n tensorflow  --clone base_env
```
The name of the new environment is `tensorflow`.  Next, activate
the environment, and install the `tensorflow` package:
```bash
$ source activate tensorflow
$ conda install -c jjh_cio_testing tensorflow-gpu
```


## Testing
In order to test whether the installation was successful, first ensure
the correct conda environment is active:
```bash
$ source activate tensorflow
```
Next, start a Python interpreter:
```bash
$ python
```
A very short sequence of Python statements should confirm that TensorFlow
is installed correctly.
```python
>>> import tensorflow as tf
```
You will get pretty verbose output about the CUDA and cuDNN libraries
being loaded, and the availabilty of a CUDA-capable GPU.
```python
>>> hello = tf.constant('hello TensorFlow!')
>>> session = tf.Session()
>>> session.run(hello)
b'hello TensorFlow!'
```
When you reach this point, we wish you happy deep learning!


## Installing TensorFlow for non-GPU systems
Unfortunately, installing a version of TensorFlow with GPU support will
not run on a system without a CUDA-capable GPU.  Hence the cleanest
approach to also run TensorFlow on non-GPU systems is to create a
separate environment for it.

Clone the `base_env` environment, and install the non-GPU version of
TensorFlow in it:
```bash
$ source deactivate
$ conda create  -n tensorflow_non_gpu  --clone base_env
```
The name of the new environment is `tensorflow_non_gpu`.  Next, activate
the environment, and install the `tensorflow` package:
```bash
$ source activate tensorflow_non_gpu
$ conda install -c jjh_cio_testing tensorflow
```


## Switching environments
To switch to another environment, simply use `activate`, e.g.,
```bash
$ source activate tensorflow_no_gpu
```
You can list all available environments by:
```bash
$ conda env list
```
To deactivate an environment, use `deactivate`, i.e.,
```bash
$ source deactivate
```


## Installing additional packages
Installing additional packages is straightforward.  First activate the
environment you want to install the package into if is not already
active:
```bash
$ source activate tensorflow
```
Next, install any package you like, e..g.,
```bash
$ conda install bokeh
```
Updating a package can be done using:
```bash
$ conda update bokeh
```
Updating all packages is trivial:
```bash
$ conda update --all
```

Removing an installed package:
```bash
$ conda remove bokeh
```
