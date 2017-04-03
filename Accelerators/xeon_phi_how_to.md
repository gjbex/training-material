# How to use the Xeon Phi nodes on thinking

Given the nature of Xeon Phi nodes, some guidelines may be useful.


## Submitting a job for Xeon Phi

The Phi nodes have their own Moab partition, so that has to be specified
on job submission.  Also, Xeon Phi nodes are marked with a PBS attribute,
so that should be specified as well.
```bash
$ qsub   -l nodes=1:ppn=12:phi  -l partition=phi  job.pbs
```


## Compiling code to run natively on Xeon Phi

The Intel compiler can do cross compilation, so there is no need to
work on the Phis themselves.  Simply adding the `-mmic` flag will do the
trick.
```bash
$ icc  -qopenmp  -mmic  -O2  -g  -o pi.exe  pi.c
```


## Login into the Phis

The MICs present themselves as Linux machines, when having a job running
on a phi node, one can `ssh` into them.
```bash
$  ssh  pbsuser@mic0
```
and
```bash
$  ssh  pbsuser@mic1
```
This access the first and second card respectively.

Transfering files to the Phis is quite similar using `scp`.
```bash
$ scp  pi.exe  pbsuser@mic0:
```


## File systems

The Phis have no access to network file systems, neither GPFS, nor NFS.
This implies that all executables, supporting libraries and input files
have to be copied to the Phis prior to executing the computation, and
that output has to be copied back, all using `scp` as described above.

Non-MPI applications can be statically linked so that no libraries need to
be transferred in addition to the executable.  For MPI application, one
would have to cpoy all relevant libraries.

To link statically, add the `-static` link flag.


## Troubleshooting

To check the status of the Phis, use `micctrl` on the host, i.e.,
```bash
$ micctrl --status
```
When the status is online, everything is probably fine.

The `miccheck` command can also come in handy.

To get more detailed information on a Phi, use `micinfo`.


## Additional information

More information is available from the [administor's guide](https://software.intel.com/sites/default/files/article/373934/system-administration-for-the-intel-xeon-phi-coprocessor.pdf).
