# SSH config

The SSH configuration file resides in the `.ssh` directory in your home
directory (at least when using Linux or MacOS X).  It is simply called
`config`.  It is not created by default, so you would have to create the
initial version.  Make sure only the  owner has read and write permission,
neither group nor world should be able to read the file.

To simplify login in to a host, say `login.hpc.kuleuven.be` as user
`vsc50005`, you can add the following:
```
Host *
    ServerAliveInterval 60

Host hpc
    HostName login.hpc.kuleuven.be
    User vsc50005
    ForwardAgent yes
    ForwardX11 yes
```

Here, you should replace `login.hpc.kuleuven.be` by the hostname of the
remote host you want to login to, and `vsc50005` by your user name on that
system.

Now you can log in simply using
```bash
$ ssh hpc
```

## Multiple keys

If you have multiple SSH key pairs to authenticate to various servers (which
is good practice), it is prudent to add a specific identity file to
authenticate to a specific server.

Host *
    ServerAliveInterval 60

Host hpc
    HostName login.hpc.kuleuven.be
    User vsc50005
    ForwardAgent yes
    ForwardX11 yes
    IdentityFile ~/.ssh/id_rsa_vsc50005
```

Here, `~/.ssh/id_rsa_vsc50005` is the private key for the host
`login.hpc.kuleuven.be`.  It is good practice to add this in case you have
multiple private keys added to an SSH agent.


## Junp hosts

To use a host as a proxy, but log in through it on another node, the
following entry can be added:
```
Host leibniz
    Hostname login.leibniz.antwerpen.vsc
    User vsc50005
    ProxyJump hpc
    ForwardAgent yes
    ForwardX11 yes
```

In this example, `login.leibniz.antwerpen.vsc` is the host you actually
want to log in to, and `login.hpc.kuleuven.be` is the host you are using
as a proxy jump hosts.


## Avoiding unwieldy config files

If you access many hosts, your `.ssh/config` file can grow very long.  In that
case, it might be convenient to group hosts into distinct files, and include
those into your main `.ssh/config` file, e.g.,
```
Include ~/.ssh/config_vsc
```
