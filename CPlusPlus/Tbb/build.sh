#!/usr/bin/env bash

INTEL_BASEDIR=/apps/leuven/thinking/2015a/software/intel
INTEL_VERSION=cluster_studio_2016
INTEL_DIR="$INTEL_BASEDIR/$INTEL_VERSION"

export INTEL_LICENSE_FILE=/apps/leuven/etc/licenses/USE_SERVER.lic

source $INTEL_DIR/bin/compilervars.sh intel64
source $INTEL_DIR/tbb/bin/tbbvars.sh intel64

make CXX=icpc \
     OMPFLAGS="-qopenmp" \
     CPPFLAGS="-I$INTEL_DIR/tbb/include" \
     LDFLAGS="-L$INTEL_DIR/tbb/lib/intel64/gcc4.4"
