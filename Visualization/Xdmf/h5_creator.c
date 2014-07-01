#include <err.h>
#include <math.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <hdf5.h>

#define XDIM 10
#define YDIM 10
#define ZDIM 10

int main(int argc, char *argv[]) {
    hid_t fileId, dataspaceId, attrspaceId, datasetId, attrId, attrTypeId,
          groupId;
    hsize_t dataDims[3];
    float x, y, z, x_delta = 0.1, y_delta = 0.1, z_delta = 0.1;
    float data[XDIM][YDIM][ZDIM];
    char unit[] = "K";
    int i, j, k;

    if (argc != 2)
        errx(EXIT_FAILURE, "no HDF5 file name given");

    /* data initialization */
    x = 0.0;
    for (i = 0; i < XDIM; i++) {
        y = 0.0;
        for (j = 0; j < YDIM; j++) {
            z = 0.0;
            for (k = 0; k < ZDIM; k++) {
                data[i][j][k] = exp(-(x*x + y*y + z*z));
                z += z_delta;
            }
            y += y_delta;
        }
        x += x_delta;
    }

    /* open file, overwriting existing file */
    fileId = H5Fcreate(argv[1], H5F_ACC_TRUNC, H5P_DEFAULT, H5P_DEFAULT);

    /* create data space */
    dataDims[0] = XDIM;
    dataDims[1] = YDIM;
    dataDims[2] = ZDIM;
    dataspaceId = H5Screate_simple(3, dataDims, NULL);

    /* create data set */
    datasetId = H5Dcreate(fileId, "/temperature", H5T_IEEE_F64LE,
                          dataspaceId, H5P_DEFAULT, H5P_DEFAULT,
                          H5P_DEFAULT);

    /* write data to HDF5 */
    H5Dwrite(datasetId, H5T_NATIVE_FLOAT, H5S_ALL, H5S_ALL,
             H5P_DEFAULT, data);

    H5Sclose(dataspaceId);

    /* create and write an attribute for the data set */
    attrspaceId = H5Screate(H5S_SCALAR);
    attrTypeId = H5Tcopy(H5T_C_S1);
    H5Tset_size(attrTypeId, strlen(unit) + 1);
    attrId = H5Acreate(datasetId, "units", attrTypeId, attrspaceId,
                       H5P_DEFAULT, H5P_DEFAULT);
    H5Awrite(attrId, attrTypeId, unit);
    H5Tclose(attrTypeId);
    H5Sclose(attrspaceId);
    H5Aclose(attrId);

    /* close data set */
    H5Dclose(datasetId);

    /* close file */                        
    H5Fclose(fileId);

    return EXIT_SUCCESS;
}

