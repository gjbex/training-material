#include <err.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <unistd.h>

#include <hdf5.h>

#define ARGV_MAX 256

int fileExists(char *fileName);
double *createMatrix(int m, int n);

int main(int argc, char *argv[]) {
    hid_t fileId;
    hsize_t dims[2];
    char fileName[ARGV_MAX], path[ARGV_MAX];
    int m, n;
    double *data;

    if (argc != 5)
        errx(EXIT_FAILURE, "expecting file, HDF5 path, m, n");

    strncpy(fileName, argv[1], ARGV_MAX);
    strncpy(path, argv[2], ARGV_MAX);
    m = atoi(argv[3]);
    n = atoi(argv[4]);
    dims[0] = m;
    dims[1] = n;

    fprintf(stderr, "writing a %dx%d matrix to '%s' in '%s'\n",
            m, n, fileName, path);

    if (fileExists(fileName))
        fileId = H5Fopen(fileName, H5F_ACC_RDWR, H5P_DEFAULT);
    else
        fileId = H5Fcreate(fileName, H5F_ACC_TRUNC, H5P_DEFAULT,
                           H5P_DEFAULT);

    data = createMatrix(m, n);

    H5LTmake_dataset_double(fileId, path, 2, dims, data);

    H5Fclose(fileId);
    return EXIT_SUCCESS;
}

int fileExists(char *fileName) {
    struct stat fstat;
    return stat(fileName, &fstat) == 0;
}

double *createMatrix(int m, int n) {
    double *matrix;
    int i;
    if ((matrix = (double *) calloc(m*n, sizeof(double))) == NULL)
        errx(EXIT_FAILURE, "can't allocate matrix");
    for (i = 0; i < m*n; i++)
        matrix[i] = ((double) rand())/RAND_MAX;
    return matrix;
}

