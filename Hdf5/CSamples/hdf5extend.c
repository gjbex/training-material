#include <err.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <unistd.h>

#include <hdf5.h>

#define RANK 2
#define XDIM 10
#define YDIM 5
#define XCHUNK 100
#define YCHUNK 5

int fileExists(char *fileName);
int getLastEntry(hid_t datasetId);

int main(int argc, char *argv[]) {
    hid_t fileId, dataspaceId, datasetId;
    hsize_t dims[] = {XDIM, YDIM};
    hsize_t dataDims[RANK];
    int data[XDIM][YDIM];
    int i, j, k = 0;

    if (argc != 2)
        errx(EXIT_FAILURE, "no HDF5 file name given");

    dataDims[0] = XDIM;
    dataDims[1] = YDIM;
    fprintf(stderr, "data dimensions (%lld,%lld)\n",
            dataDims[0], dataDims[1]);

    /* if file exists, open it, else, create it */
    if (fileExists(argv[1]))
        fileId = H5Fopen(argv[1], H5F_ACC_RDWR, H5P_DEFAULT);
    else
        fileId = H5Fcreate(argv[1], H5F_ACC_TRUNC, H5P_DEFAULT,
                           H5P_DEFAULT);

    /* try to open the dataset, if it does not exist, create it */
    if (H5Lexists(fileId, "/values", H5P_DEFAULT) == 0) {
        /* create data space */
        hsize_t maxDataDims[RANK] = {H5S_UNLIMITED, H5S_UNLIMITED};
        dataspaceId = H5Screate_simple(RANK, dataDims, maxDataDims);

        /* set chunking property */
        hsize_t chunkDims[RANK] = {XCHUNK, YCHUNK};
        hid_t creationProp = H5Pcreate(H5P_DATASET_CREATE);
        H5Pset_chunk(creationProp, RANK, chunkDims);

        /* create data set */
        datasetId = H5Dcreate(fileId, "/values", H5T_STD_I32LE,
                              dataspaceId, H5P_DEFAULT, creationProp,
                              H5P_DEFAULT);
    } else {
        datasetId = H5Dopen(fileId, "/values", H5P_DEFAULT);
        k = getLastEntry(datasetId);
        /* extend the dataset */
        dataspaceId = H5Dget_space(datasetId);
        H5Sget_simple_extent_dims(dataspaceId, dims, NULL);
        fprintf(stderr, "size now (%lld,%lld)\n", dims[0], dims[1]);
        hsize_t newSize[RANK] = {dims[0] + dataDims[0], dims[1]};
        H5Dextend(datasetId, newSize);
        dataspaceId = H5Dget_space(datasetId);
        H5Sget_simple_extent_dims(dataspaceId, dims, NULL);
        fprintf(stderr, "size enlarged to (%lld,%lld)\n", dims[0], dims[1]);
    }

    /* data initialization */
    for (i = 0; i < XDIM; i++)
        for (j = 0; j < YDIM; j++)
            data[i][j] = ++k;

    /* create a memory hyperslab, should cover all of data */
    hid_t memspaceId = H5Screate_simple(RANK, dims, NULL);
    hsize_t memOffset[RANK] = {0, 0};
    fprintf(stderr, "memory offset (%lld,%lld), count(%lld,%lld)\n",
            memOffset[0], memOffset[1], dataDims[0], dataDims[1]);
    H5Sselect_hyperslab(memspaceId, H5S_SELECT_SET, memOffset, NULL,
                        dataDims, NULL);

    /* create dataset hyperslab, should cover newly extended part */
    hsize_t offset[RANK] = {dims[0] - dataDims[0], 0};
    fprintf(stderr, "file offset (%lld,%lld), count(%lld,%lld)\n",
            offset[0], offset[1], dataDims[0], dataDims[1]);
    H5Sselect_hyperslab(dataspaceId, H5S_SELECT_SET, offset, NULL,
                        dataDims, NULL);

    /* write data to HDF5 */
    H5Dwrite(datasetId, H5T_NATIVE_INT, memspaceId, dataspaceId,
             H5P_DEFAULT, data);


    /* close stuff */
    H5Sclose(dataspaceId);
    H5Sclose(memspaceId);
    H5Dclose(datasetId);
    H5Fclose(fileId);

    return EXIT_SUCCESS;
}

int fileExists(char *fileName) {
    struct stat fstat;
    return stat(fileName, &fstat) == 0;
}

int getLastEntry(hid_t datasetId) {
    int k;

    hsize_t memDim = 1;
    hid_t memspaceId = H5Screate_simple(1, &memDim, NULL);
    hsize_t memOffset = 0;
    H5Sselect_hyperslab(memspaceId, H5S_SELECT_SET, &memOffset, NULL,
                        &memDim, NULL);

    hsize_t dims[RANK];
    hid_t dataspaceId = H5Dget_space(datasetId);
    H5Sget_simple_extent_dims(dataspaceId, dims, NULL);
    hsize_t offset[] = {dims[0] - 1, dims[1] - 1};
    hsize_t count[] = {1, 1};
    H5Sselect_hyperslab(dataspaceId, H5S_SELECT_SET, offset, NULL,
                        count, NULL);

    H5Dread(datasetId, H5T_NATIVE_INT, memspaceId, dataspaceId,
            H5P_DEFAULT, &k);
    return k;
}

