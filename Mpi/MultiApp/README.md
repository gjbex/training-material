# MultiApp
It is possible to establish MPI communication between MPI applications.
Here, two approaches are illustrated, the first where both applications
share a communicator, the second in a client/server setup where each
application has its own communicator, and an explicit communicator is
created for the intercommunication.  This approach is more suited when
the code is littered with direct use of `MPI_COMM_WORLD`.

## What is it?
1. `appl.c`: MPI application to illustrate that applications can share an
    `MPI_COMM_WORLD` communicator when launched by `mpirun`.
1. `run_single_communicator.sh`: Bash script to run `appl1.exe` and
    `appl2.exe` to illustrate the first approach.
1. `server.c`: MPI application that acts as a server, opening a port to
    accept MPI communication from a client application.
1. `client.c`: MPI application that acts as a client, connecting to a
    port of a server MPI application, and sending information to it using
    MPI.
1. `run_client_server.sh`: Bash script that runs the client/server setup.
1. `Makefile`: make file to build the applications.
