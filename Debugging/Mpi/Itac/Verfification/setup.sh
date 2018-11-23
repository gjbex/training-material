ITAC_DIR="/opt/intel/itac/2018.1.017/"
IMPI_DIR="/opt/intel/impi/2018.1.163/"
source /opt/intel/bin/compilervars.sh intel64
source "${IMPI_DIR}/bin64/mpivars.sh" intel64
export LD_LIBRARY_PATH="${ITAC_DIR}/slib:${ITAC_DIR}/slib/slib_common:${LD_LIBRARY_PATH}"
