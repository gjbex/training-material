# Service
Singularity images can be run as daemons when started as instances.
This example implements that for Alpino.

## What is it?
1. `xenial_alpino_docker.def`: Singularity image recipe file for
    building from a docker container, also illustrates
    `%labels` meta-information featrure.
1. `alpino.sh`: `init.d` script to start and stop Alpino as a server.
1. `conf`: directory containing a file with the port number to be used.
1. 'alpino.pbs`: PBS script demonstrating how to run multiple
    instances of the Alpino server using the worker framework.
1. `text`: sample input for the PBS job.

## How to use?
1. `Ensure that a valid and unique port number is the `port_nr` file
    in a directory that is bound to `/conf` in the image.  Here, such
    a file is in the `conf` subdirectory.
1. Run the Singularity image as an instance with name `alpino`:
    `$ singularity instance.start -B conf:/conf alpino.simg alpino`
1. Run clients to your heart's content.
1. Stop the instance using: `$ singularity instance.stop alpino`
