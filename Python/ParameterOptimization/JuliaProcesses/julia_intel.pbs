#!/usr/bin/env bash
#PBS -A lp_sys
#PBS -l nodes=1:ppn=24:haswell
#PBS -l pmem=2gb
#PBS -l walltime=03:00:00
#PBS -j oe
#PBS -m ae
#PBS -M geertjan.bex@uhasselt.be

cd $PBS_O_WORKDIR

source switch_to_2018a
module load intel

# ensure the executable is op to date
make CXX=icpc CXXFLAGS='-qopenmp -std=c++14 -O2' clean all
if [[ $? -ne 0 ]]
then
    (>&2 echo "### error: make failed")
    exit 1
fi

module load conda
source activate hyperopt

./julia_optimize.py --max-ppn 20 --max-evals 100 \
                    --trials trials_intel.txt
