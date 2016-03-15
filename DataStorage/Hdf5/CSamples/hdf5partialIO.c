#include <err.h>
#include <stdio.h>
#include <stdlib.h>
#include <hdf5.h>

int main(int argc, char *argv[]) {
    hid_t fileId, datasetId, dataspaceId, memspaceId;
    int rank, r;
    unsigned long i, j;
    hsize_t dims[2], offset[2], count[2], memOffset[1], memCount[1];
    herr_t status;
    double *data;

    if (argc < 2)
        errx(EXIT_FAILURE, "no file specified");

    fileId = H5Fopen(argv[1], H5F_ACC_RDONLY, H5P_DEFAULT);
    datasetId = H5Dopen(fileId, "/values", H5P_DEFAULT);
    dataspaceId = H5Dget_space(datasetId);
    rank = H5Sget_simple_extent_ndims(dataspaceId);
    H5Sget_simple_extent_dims(dataspaceId, dims, NULL);
    printf("rank = %d, [", rank);
    for (r = 0; r < rank; r++)
        printf("%lu%s", (unsigned long) dims[r],
               r == rank - 1 ? "]\n" : ",");
    offset[1] = 0;
    count[0] = 1;
    count[1] = dims[1];
    data = (double *) calloc(dims[1], sizeof(double));
    if (!data)
        errx(EXIT_FAILURE, "can't allocate array");

    memspaceId = H5Screate_simple(1, &dims[1], NULL);
    memOffset[0] = 0;
    memCount[0] = dims[1];
    H5Sselect_hyperslab(memspaceId, H5S_SELECT_SET, memOffset, NULL,
                        memCount, NULL);
    
    for (i = 0; i < dims[0]; i++) {
        offset[0] = i;
        H5Sselect_hyperslab(dataspaceId, H5S_SELECT_SET, offset, NULL,
                            count, NULL);
        H5Dread(datasetId, H5T_NATIVE_DOUBLE, memspaceId, dataspaceId,
                H5P_DEFAULT, data);

        printf("%d: ", i);
        for (j = 0; j < dims[1]; j++)
            printf("%5.1f%s", data[j], j == dims[1] - 1 ? "\n" : "");
    }

    H5Sclose(memspaceId);
    H5Sclose(dataspaceId);
    H5Dclose(datasetId);
    H5Fclose(fileId);

    free(data);
    return EXIT_SUCCESS;
}

