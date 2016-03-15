#include <err.h>
#include <stdio.h>
#include <stdlib.h>
#include <hdf5.h>

int main(int argc, char *argv[]) {
    hid_t fileId, datasetId, dataspaceId, attrId, attrType;
    int rank, r;
    unsigned long i, j;
    hsize_t *dims;
    size_t attrSize;
    herr_t status;
    double *data;
    char unitStr[80];

    if (argc < 2)
        errx(EXIT_FAILURE, "no file specified");
    if (argc < 3)
        errx(EXIT_FAILURE, "no data set specified");

    fileId = H5Fopen(argv[1], H5F_ACC_RDONLY, H5P_DEFAULT);
    datasetId = H5Dopen(fileId, argv[2], H5P_DEFAULT);
    dataspaceId = H5Dget_space(datasetId);
    rank = H5Sget_simple_extent_ndims(dataspaceId);
    if (rank != 2)
        errx(EXIT_FAILURE, "expected data of rank 2, not %d\n", rank);
    dims = (hsize_t *) calloc(rank, sizeof(hsize_t));
    H5Sget_simple_extent_dims(dataspaceId, dims, NULL);
    printf("rank = %d, [", rank);
    for (r = 0; r < rank; r++)
        printf("%lu%s", (unsigned long) dims[r],
               r == rank - 1 ? "]\n" : ",");
    H5Sclose(dataspaceId);

    data = (double *) calloc(dims[0]*dims[1], sizeof(double));
    if (!data)
        errx(EXIT_FAILURE, "can't allocate array");

    H5Dread(datasetId, H5T_NATIVE_DOUBLE, H5S_ALL, H5S_ALL, H5P_DEFAULT,
            data);

    for (i = 0; i < dims[0]; i++)
        for (j = 0; j < dims[1]; j++)
            printf("%5.1f%s", data[i*dims[1] + j],
                   j == dims[1] - 1 ? "\n" : "");

    attrId = H5Aopen_by_name(datasetId, ".", "units",
                             H5P_DEFAULT, H5P_DEFAULT);
    attrType = H5Aget_type(attrId);

    H5Aread(attrId, attrType, unitStr);
    printf("units: '%s'\n", unitStr);

    H5Tclose(attrType);
    H5Aclose(attrId);
    H5Dclose(datasetId);
    H5Fclose(fileId);

    free(dims);
    free(data);

    return EXIT_SUCCESS;
}

