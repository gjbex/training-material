# Paramiko
Paramiko is a non-standard Python library for working with SSH.  It can
be used to execute command on a remote host, or perform file transfers
using the SFTP protocol.

## What is it?
1. `ssh.py`: module with some SSH connection utitlity functions, imported
    in the scripts.
1. `ls.py`: performs an `ls` command for the specified directory on a
    remote host.
1. `gbalance.py`: performs a `gbalance` MAM command on the remote server,
    will only work on the KU Leuven/UHasselt VSC infrastructure.
1. `module_av.py`: performs a `module av` command on the remote server for
    the specified software package, will only work on the
    KU Leuven/UHasselt VSC infrastructure.
1. `wc.py`: example of executing a command on a remote machine that reads
    from standard input, and writes to standard output/error.
