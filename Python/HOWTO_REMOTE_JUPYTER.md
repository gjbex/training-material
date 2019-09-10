# How to run a Jupyter notebook on a compute node

Jupyter notebooks provide a very convenient way for Python programmers
to explore and visualize data interactively, or do explorative programming.
Typically, a notebook server runs on your own computer, and you connect
to it using a web browser (actually, the web browser will be started
automatically).

Although this is very convenient and easy to use, for more computationally
intensive work you may want to run the notebook server on a compute node
of a VSC cluster.


## Prerequisite:

The most convenient way to install Jupyter, and any other Python packages
you require is using conda.  In case you're not familiar with conda, please
check out the [quickstart guide](INSTALL_CONDA.md).  In this how-to, we will
assume that the conda environment's name that has Jupyter installed is
`science`.  We will also assume that the `$VSC_DATA/miniconda3/bin`
directory is in your `PATH` variable.

## General procedure 

The general procedure is to first start a notebook server, then set up an SSH tunnel and, finally, open an interface on your local machine.

### Start a job and a Jupyter notebook

First, start an interactive job on a compute node, and launch Jupyter
notebook on that node.

  1. Log in to the login node using ssh:

     ```bash
     local$ ssh vscxxxxx@login.hpc.kuleuven.be
     ```

  1. As the Jupyter notebook server has to run on a compute node, we first start an interactive job:

     ```bash
     login$ qsub -I -l nodes=1:ppn=3 -l walltime=03:00:00
     ```

     The `-I` flag specifies this is an interactive job, and we request 4 hours walltime.  Note that you would probably have to add the `-A` option with the project to debit for credits. Note that GPUs are also supported:

     ```bash
     login$ qsub -I -A lp_my_project -l nodes=1:ppn=9:gpus=1 \
               -l partition gpu -l walltime=03:00:00
     ```

  1. Once your job starts, you'll see the name of the node the job is running on in the shell prompt.  In this tutorial, we will assume it is `node-id`. Navigate to the relevant directory where your notebook is stored, or where you intend to create a new one (e.g. `$VSC_DATA`). In that directory, activate your environment:

     ```bash
     node-id$ source activate science
     ```

  1. Start the Jupyter notebook using a unique port number (preferably your VSC number vscxxxxx):

     ```bash
     node-id$ jupyter notebook --port xxxxx
     ```
     Please take note of the last line of output reported by Jupyter on the terminal, as this will be the URL to which you will point your web browser. This URL will be formatted as follows

     ```bash
      http://localhost:8888/?token=56262fe0755d2321911f96df8c3c98e651f24238452035d9
     ```

     but will contain a different security token. 

### Set up SSH tunnel

#### Without using NX login nodes

Next, you set up a tunnel from your machine to the node where the notebook is running.

```
local$ ssh -J vscxxxxx@login.hpc.kuleuven.be \
           -L xxxxx:localhost:xxxxx                 \
           vscxxxxx@node-id
```

*Note:* this command will not exit, if you like to do everything in one
terminal, put the process in the background using `&`.

#### Using NX login nodes

An easier alternative is to use the
NX login nodes, since this provides a GUI environment on a cluster login
node.  The installation and setup of the NoMachine software on your computer
is documented on the VSC
[User Portal](https://vlaams-supercomputing-centrum-vscdocumentation.readthedocs-hosted.com/en/latest/access/nx_start_guide.html?highlight=nomachine).
Once NoMachine is installed and configured, you can connect to the cluster.

First, we have to establish an SSH tunnel from the NX login node to the
compute node.  This is required so that the web browser running on the
login node can communicate with the Jupyter server on the compute node.

On the NX login node, start another shell, and create a tunnel to the
compute node (`node-id`).  As a port number, use the five digits of your
VSC account, this should ensure that there are no conflicts, e.g., if your
VSC account is vscxxxxx, use xxxxx as port number:
```bash
ssh -L xxxxx:localhost:8888 -N node-id.genius.hpc.kuleuven.be
```

### Open the interface to the Jupyter notebook

Finally, open your web browser on your local machine or NX login node, copy/paste the
link that the Jupyter notebook has reported on the compute note into your browser, and *presto!*
