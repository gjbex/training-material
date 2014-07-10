#include <err.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <hdf5.h>

#define XDIM 10
#define YDIM 5
#define VDIM 17
#define XIDIM 12
#define YIDIM 3

int main(int argc, char *argv[]) {
    hid_t fileId, dataspaceId, attrspaceId, datasetId, attrId, attrTypeId,
          groupId;
    hsize_t dataDims[2];
    double data[XDIM][YDIM], x;
    int data_vector[VDIM], data_matrix[XIDIM][YIDIM];
    char unit[] = "km/s";
    int i, j, k = 0;

    if (argc != 2)
        errx(EXIT_FAILURE, "no HDF5 file name given");

    /* data initialization */
    for (i = 0; i < XDIM; i++)
        for (j = 0; j < YDIM; j++)
            data[i][j] = (i + 1) + 0.1*(j + 1);
    for (i = 0; i < VDIM; i++)
        data_vector[i] = 1 + 2*i;
    for (i = 0; i < XIDIM; i++)
        for (j = 0; j < YIDIM; j++)
            data_matrix[i][j] = ++k;

    /* open file, overwriting existing file */
    fileId = H5Fcreate(argv[1], H5F_ACC_TRUNC, H5P_DEFAULT, H5P_DEFAULT);

    /* create data space */
    dataDims[0] = XDIM;
    dataDims[1] = YDIM;
    dataspaceId = H5Screate_simple(2, dataDims, NULL);

    /* create data set */
    datasetId = H5Dcreate(fileId, "/values", H5T_IEEE_F64LE, dataspaceId,
                          H5P_DEFAULT, H5P_DEFAULT, H5P_DEFAULT);

    /* write data to HDF5 */
    H5Dwrite(datasetId, H5T_NATIVE_DOUBLE, H5S_ALL, H5S_ALL,
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

    dataDims[0] = VDIM;
    dataspaceId = H5Screate_simple(1, dataDims, NULL);
    datasetId = H5Dcreate(fileId, "/vector", H5T_STD_I32LE, dataspaceId,
                          H5P_DEFAULT, H5P_DEFAULT, H5P_DEFAULT);
    H5Dwrite(datasetId, H5T_NATIVE_INT, H5S_ALL, H5S_ALL,
             H5P_DEFAULT, data_vector);
    H5Sclose(dataspaceId);
    H5Dclose(datasetId);

    dataDims[0] = XIDIM;
    dataDims[1] = YIDIM;
    dataspaceId = H5Screate_simple(2, dataDims, NULL);
    datasetId = H5Dcreate(fileId, "/matrix", H5T_STD_I32LE, dataspaceId,
                          H5P_DEFAULT, H5P_DEFAULT, H5P_DEFAULT);
    H5Dwrite(datasetId, H5T_NATIVE_INT, H5S_ALL, H5S_ALL,
             H5P_DEFAULT, data_matrix);
    H5Sclose(dataspaceId);
    H5Dclose(datasetId);

    groupId = H5Gcreate(fileId, "/validation", H5P_DEFAULT, H5P_DEFAULT, H5P_DEFAULT);
    x = 0.0;
    for (i = 0; i < XDIM; i++)
        for (j = 0; j < YDIM; j++) {
            data[i][j] = x;
            x += 0.123;
        }
    dataDims[0] = XDIM;
    dataDims[1] = YDIM;
    dataspaceId = H5Screate_simple(2, dataDims, NULL);

    /* create data set */
    datasetId = H5Dcreate(fileId, "/validation/values", H5T_IEEE_F64LE,
                          dataspaceId, H5P_DEFAULT, H5P_DEFAULT,
                          H5P_DEFAULT);

    /* write data to HDF5 */
    H5Dwrite(datasetId, H5T_NATIVE_DOUBLE, H5S_ALL, H5S_ALL,
             H5P_DEFAULT, data);

    H5Sclose(dataspaceId);
    H5Dclose(datasetId);
    H5Gclose(groupId);

    /* close file */                        
    H5Fclose(fileId);

    return EXIT_SUCCESS;
}

