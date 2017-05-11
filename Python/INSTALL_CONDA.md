# How to install Python packages using conda
Here, we describe how to install Python packages using conda.


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
You will be asked a number of questions. Note that the location of the
installation directory is very important.  `conda` tneds to use a lot
of disk space, and you'll easily exceed your disk quota, so install in
your data directory.  To get that path, execute
```bash
$ echo $VSC_DATA
```

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
$ conda create  -n science  numpy scipy matplotlib
```
This command creates a new conda environment called `science`, and
installs a number of Python packages that you will probably want to have
handy in any case to preprocess, visualize, or postprocess your data.
You can of course install more, depending on your requirements and
personal taste.


## Working with the environment
To work with an environment, you have to activate it.  This is done with,
e.g.,
```bash
$ source activate science
```
Here, `science` is the name of the environment you want to work in.


## Install an additoinal package
To install an additoinal package, e.g., `pandas`, first ensure that the
environment you want to work in is activated.
```bash
$ source activate tensorflow
```
Next, install the package
```bash
$ conda install -c jjh_cio_testing tensorflow-gpu
```


## Updating
Using `conda`, it is easy to keep your packages up-to-date.

Updating a single package (and its dependencies) can be done using:
```bash
$ conda update pandas
```
Updating all packages is trivial:
```bash
$ conda update --all
```

Removing an installed package:
```bash
$ conda remove bokeh
```
