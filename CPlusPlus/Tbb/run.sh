#!/usr/bin/env bash

INTEL_BASEDIR=/apps/leuven/thinking/2015a/software/intel
INTEL_VERSION=cluster_studio_2016
INTEL_DIR="$INTEL_BASEDIR/$INTEL_VERSION"

source $INTEL_DIR/bin/compilervars.sh intel64
source $INTEL_DIR/tbb/bin/tbbvars.sh intel64

# echo "$@" I
$@
