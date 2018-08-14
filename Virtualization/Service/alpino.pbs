#!/bin/bash -l
#PBS -A lpt2_pilot_2018
#PBS -l nodes=1:ppn=36
#PBS -l walltime=00:05:00

cd $PBS_O_WORKDIR

# if no input file is given, exit
if [ -z $input_file ]
then
    echo "no input file given"
    exit 1
fi

# when not running as worker item, initialize WORKER_RANK to 1
if [ -z "${WORKER_RANK}" ]
then
    WORKER_RANK=1
fi

>&2 echo "starting server..."
# use the VSC number as the base port number, start each server with
# listening to its own port
base_port="${USER:3:5}"
alpino_server_port=$(( ${base_port} + ${WORKER_RANK} ))

# create the configuration directory for this instance with the file
# containing the port number to use by the instance
conf_dir="./conf_${alpino_server_port}"
mkdir -p "${conf_dir}"
echo "${alpino_server_port}" > "${conf_dir}/port_nr"

# determine instance name, and start it
alpino_instance="alpino_${alpino_server_port}"
singularity instance.start -B "${conf_dir}":/conf alpino.simg \
    "${alpino_instance}"

# give the server time to initalize
sleep 10
>&2 echo "started server"

mkdir -p output

# read the lines of the input file, sending each to the server
alpino_server_host='localhost'
out="output/out-${alpino_server_port}-${input_file}"
line_nr=0
while IFS='' read -r line || [[ -n "$line" ]]; do
    line_nr=$(( $line_nr + 1 ))
    echo "$line" | nc $alpino_server_host $alpino_server_port \
        >> "${out}"
done < "text/$input_file"

>&2 echo "${line_nr} lines processed, exiting..."

# stop the server
singularity instance.stop "${alpino_instance}"

# give the server some time to come down gracefully
sleep 10

# remove configuration directory
rm -rf "${conf_dir}"
