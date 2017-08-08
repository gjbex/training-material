# How to run a Jupyter notebook on a compute node

Jupyter notebooks provide a very convenient way for Python programmers
to explore and visualize data interactively, or do explorative programming.
Typically, a notebook server runs on your own computer, and you connect
to it using a web browser (actually, the web browser will be started
automatically).

Although this is very convenient and easy to use, for more computationally
intensive work you may want to run the notebook server on a compute node
of a VSC cluster (we'll assume you using thinking here, but the apporoach
works for all our clusters).


## Prerequistes

Some software installation and configuration is required before you can get
started.

### NoMachine

Although alternatives exist, the easiest approach is to use the
NX login nodes, since this provides a GUI environment on a cluster login
node.  The installation and setup of the NoMachine software on your computer
is documented on the VSC
[User Portal](https://www.vscentrum.be/client/multiplatform/nx-start-guide).
Once NoMachine is installed and configured, you can connect to the cluster.

### Installing Jupyter

The most convenient way to install Jupyter, and any other Python packages
you require is using conda.  In case you're not familiar with conda, please
check out the [quickstart guide](INSTALL_CONDA.md).  In this how-to, we will
assume that the conda environment's name that has Jupyter installed is
`science`.  We will also assume that the `$VSC_DATA/miniconda3/bin`
directory is in your `PATH` variable.


## Using a notebook

### Starting the server

The first step is to run a Jupyter notebook server, since this has to be
done on a compute node, we first start an interactive job.
```bash
$ qsub  -I  -l walltime=4:00:00
```
The `-I` flag specifies this is an interactive job, and we request 4 hours
walltime.  Note that you would probably have to add the `-A` option with
the project to debit for credits.

Once your job starts, you'll see the name of the node the job is running
on in the shell prompt.  In this tutorial, we will assume it is `r5i1n7`.

Navigate to the relevant directory where your notebook is stored, or where
you intend to create a new one.

Load the conda environment, `science` in this tutorial:
```bash
$ source activate science
```

Start a Jupyter notebook server:
```bash
$ jupyter notebook
```
When Jupyter has started, the last line of output will be the URL to
point your web browser to, e.g.,
```
 http://localhost:8888/?token=56262fe0755d2321911f96df8c3c98e651f24238452035d9
 ```
### Connecting the client

First, we have to establish an SSH tunnel from the NX login node to the
compute node.  This is required so that the web browser running on the
login node can communicate with the Jupyter server on the compute node.

On the NX login node, start another shell, and create a tunnel to the
compute node (`r5i1n7`).  As a port number, use the five digits of your
VSC account, this should ensure that there are no conflicts, e.g., if your
VSC account is vsc30140, use 30140 as port number:
```bash
ssh -L 30140:localhost:8888 -N r5i1n7
```

Now, start firefox on the NX login node, and browse to the link the
Jupyter notebook server displayed.  Enjoy.
