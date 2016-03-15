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
    H5T_class_t classId;
    size_t typeSize;
    char path1[ARGV_MAX + 1], path2[ARGV_MAX + 1], path3[ARGV_MAX + 1],
         fileName[ARGV_MAX + 1];
    int m, n, k, i, j, l;
    double *data1, *data2, *data3;

    if (argc != 5)
        errx(EXIT_FAILURE, "expecting file, path1, path2, path3");

    strncpy(fileName, argv[1], ARGV_MAX);
    
    if (fileExists(fileName))
        fileId = H5Fopen(argv[1], H5F_ACC_RDWR, H5P_DEFAULT);
    else
        errx(EXIT_FAILURE, "file '%s' does not exist", fileName);

    strncpy(path1, argv[2], ARGV_MAX);
    strncpy(path2, argv[3], ARGV_MAX);
    strncpy(path3, argv[4], ARGV_MAX);

    H5LTget_dataset_info(fileId, path1, dims, &classId, &typeSize);
    if (!(data1 = (double *) calloc(dims[0]*dims[1], sizeof(double))))
        errx(EXIT_FAILURE, "can't allocate array");
    m = dims[0];
    k = dims[1];
    H5LTread_dataset_double(fileId, path1, data1);

    H5LTget_dataset_info(fileId, path2, dims, &classId, &typeSize);
    if (dims[0] != k)
        errx(EXIT_FAILURE, "dimension mismatch: %dx%d vs. %dx%d",
                m, k, dims[0], dims[1]);
    n = dims[1];
    if (!(data2 = (double *) calloc(dims[0]*dims[1], sizeof(double))))
        errx(EXIT_FAILURE, "can't allocate array");
    H5LTread_dataset_double(fileId, path2, data2);

    if (!(data3 = (double *) calloc(m*n, sizeof(double))))
        errx(EXIT_FAILURE, "can't allocate array");
    for (i = 0; i < m; i++)
        for (j = 0; j < n; j++) {
            data3[i*n + j] = 0.0;
            for (l = 0; l < k; l++)
                data3[i*n + j] += data1[i*k + l]*data2[l*n + j];
        }

    dims[0] = m;
    dims[1] = n;
    H5LTmake_dataset_double(fileId, path3, 2, dims, data3);

    fprintf(stderr, "writing a %dx%d matrix to '%s' in '%s'\n",
            m, n, fileName, path3);

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


