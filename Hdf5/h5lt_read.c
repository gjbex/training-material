#include <err.h>
#include <stdio.h>
#include <stdlib.h>
#include <hdf5.h>

int main(int argc, char *argv[]) {
    hid_t fileId;
    unsigned long i, j;
    double *data;
    int rank;
    hsize_t *dims;
    H5T_class_t classId;
    size_t typeSize;

    if (argc < 2)
        errx(EXIT_FAILURE, "no file specified");
    if (argc < 3)
        errx(EXIT_FAILURE, "no data set specified");

    fileId = H5Fopen(argv[1], H5F_ACC_RDONLY, H5P_DEFAULT);
    H5LTget_dataset_ndims(fileId, argv[2], &rank);
    dims = (hsize_t *) calloc(rank, sizeof(hsize_t));
    printf("rank = %d\n", rank);
    H5LTget_dataset_info(fileId, argv[2], dims, &classId, &typeSize);
    if ((data = (double *) calloc(dims[0]*dims[1], sizeof(double))) == NULL)
        errx(EXIT_FAILURE, "can't allocate array");
    H5LTread_dataset_double(fileId, argv[2], data);

    for (i = 0; i < dims[0]; i++)
        for (j = 0; j < dims[1]; j++)
            printf("%5.1f%s", data[i*dims[1] + j],
                   j == dims[1] - 1 ? "\n" : "");

    H5Fclose(fileId);

    free(data);

    return EXIT_SUCCESS;
}

