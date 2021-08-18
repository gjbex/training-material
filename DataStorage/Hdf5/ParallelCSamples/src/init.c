#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <hdf5.h>

#include "init.h"

void get_mode(int argc, char *argv[], MPI_Comm comm, int *mode) {
    int comm_rank;
    MPI_Comm_rank(comm, &comm_rank);
    if (comm_rank == 0) {
        if (argc == 1) {
            fprintf(stderr, "# error: no command line arguments");
            MPI_Abort(MPI_COMM_WORLD, EXIT_FAILURE);
        }
        if (strncmp("new", argv[1], 4) == 0) {
            *mode = NEW_MODE;
        } else if (strncmp("restart", argv[1], 8) == 0) {
            *mode = RESTART_MODE;
        } else {
            fprintf(stderr, "# error: unknown mode\n");
            MPI_Abort(comm, EXIT_FAILURE);
        }
    }
    MPI_Bcast(mode, 1, MPI_INT, 0, comm);
}

void get_file_name(int argc, char *argv[], MPI_Comm comm,
                   char file_name[MAX_STR_LEN]) {
    int comm_rank;
    MPI_Comm_rank(comm, &comm_rank);
    if (comm_rank == 0) {
        if (argc < 3) {
            fprintf(stderr, "# error: no file name specified\n");
            MPI_Abort(comm, EXIT_FAILURE);
        }
        strncpy(file_name, argv[2], MAX_STR_LEN);
    }
    MPI_Bcast(file_name, MAX_STR_LEN, MPI_CHAR, 0, comm);
}

void get_dims_from_cl(int argc, char *argv[], MPI_Comm comm,
                      int dims[RANK]) {
    int comm_rank;
    MPI_Comm_rank(comm, &comm_rank);
    if (comm_rank == 0) {
        if (argc == 3 + RANK) {
            dims[0] = atoi(argv[3]);
            dims[1] = atoi(argv[4]);
        } else {
            dims[0] = DEFAULT_X;
            dims[1] = DEFAULT_Y;
        }
    }
    MPI_Bcast(dims, 2, MPI_INT, 0, comm);
}

void get_dims_from_file(char file_name[MAX_STR_LEN], MPI_Comm comm,
                        int dims[RANK]) {
    int comm_rank;
    MPI_Comm_rank(comm, &comm_rank);
    if (comm_rank == 0) {
        const int data_rank = 1;
        hid_t file_id, dset_id, file_space;
        hsize_t h5_dims[data_rank];
        /* open HDF5 file */
        file_id = H5Fopen(file_name, H5F_ACC_RDONLY, H5P_DEFAULT);
        /* retrieve x-dimension */
        h5_dims[0] = 0;
        dset_id = H5Dopen(file_id, "x", H5P_DEFAULT);
        file_space = H5Dget_space(dset_id);
        H5Sget_simple_extent_dims(file_space, h5_dims, NULL);
        dims[0] = (int) h5_dims[0];
        H5Dclose(dset_id);
        H5Sclose(file_space);
        /* retrieve y-dimension */
        h5_dims[0] = 0;
        dset_id = H5Dopen(file_id, "y", H5P_DEFAULT);
        file_space = H5Dget_space(dset_id);
        H5Sget_simple_extent_dims(file_space, h5_dims, NULL);
        dims[1] = (int) h5_dims[0];
        H5Dclose(dset_id);
        H5Sclose(file_space);
        /* close file */
        H5Fclose(file_id);
    }
    MPI_Bcast(dims, 2, MPI_INT, 0, comm);
}

