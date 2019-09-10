# How to install Python packages using conda
Here, we describe how to install Python packages using conda.


## Installing Miniconda
If you have Miniconda already installed, you can skip ahead to the next
section, if Miniconda is not installed, we start with that. Download the
Bash script that will install it from
[conda.io](https://repo.continuum.io/miniconda/Miniconda3-latest-Linux-x86_64.sh)
using, e.g., `wget`:
```bash
$ wget https://repo.continuum.io/miniconda/Miniconda3-latest-Linux-x86_64.sh
```

Once downloaded, run the script:
```bash
$ bash Miniconda3-latest-Linux-x86_64.sh -b -p $VSC_DATA/miniconda3
```

Note that it is important to choose the Miniconda installation directory
wisely, i.e., on a file system where your quota are large enough.  Environments
may take considerable disk space.

## Configuring Miniconda

To use Miniconda, we must add the path to the Miniconda installation to the `PATH` environment variable:
```bash
export PATH="${VSC_DATA}/miniconda3/bin:${PATH}"
```
Optionally, you can add that path in your `.bashrc` file.  This is convenient,
but may lead to conflicts when working with the module system.


## Creating an environment
First, ensure that the Miniconda installation is in your `PATH` environment
variable.  The following command should return the full path to the `conda`
executable:
```bash
$ which conda
```
If the result is blank, or reports that `conda` can not be found, modify
the `PATH` environment variable appropriately by adding Miniconda's
`bin` directory to `PATH`.

At this point, you may wish to load a module for a recent compiler (GCC
is likely causing the least problems).  Note that this module should also
be loaded when using the environment you are about to create.

Creating a new conda environment is straightforward:
```bash
$ conda create  -n science  numpy scipy matplotlib jupyter
```
This command creates a new conda environment called `science`, and
installs a number of Python packages that you will probably want to have
handy in any case to preprocess, visualize, or postprocess your data.
You can of course install more, depending on your requirements and
personal taste.

This will default to the latest Python 3 version, if you need a specific version,
e.g., Python 2.7.x, this can be specified as follows:
```
$ conda create -n science  python=2.7  numpy scipy matplotlib jupyter
```


## Working with the environment
To work with an environment, you have to activate it.  This is done with,
e.g.,
```bash
$ source activate science
```
Here, `science` is the name of the environment you want to work in.


## Install an additional package
To install an additional package, e.g., `tensorflow-gpu`, first ensure that the
environment you want to work in is activated.
```bash
$ source activate science
```
Next, install the package
```bash
$ conda install -c jjh_cio_testing tensorflow-gpu
```


## Updating
Using `conda`, it is easy to keep your packages up-to-date.

Updating a single package (and its dependencies) can be done using:
```bash
$ conda update tensorflow-gpu
```
Updating all packages is trivial:
```bash
$ conda update --all
```

Removing an installed package:
```bash
$ conda remove tensorflow-gpu
```

## Deactivating an environment
To stop using an active environment, and return your shell to its original state, use the following command:
```bash
$ source deactivate
```

## More information
Additional information on conda can be found on its [documentation site](https://conda.readthedocs.io/en/latest/).
