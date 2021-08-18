#include <stdio.h>
#include <stdlib.h>
#include <mpi.h>
#include <hdf5.h>

int main(int argc, char *argv[]) {
    int data_rank = 2;
    long n_x = 8, n_y = 5;
    int rank, size;
    MPI_Info info = MPI_INFO_NULL;
    hid_t file_id, plist_id, dset_id, filespace, memspace;
    hsize_t data_dims[] = {n_x, n_y};
    hsize_t count[data_rank], offset[data_rank], write_count[data_rank], write_offset[data_rank];
    herr_t status;
    int *data;
    int i, j;

    /* MPI initialization */
    MPI_Init(&argc, &argv);
    MPI_Comm_rank(MPI_COMM_WORLD, &rank);
    MPI_Comm_size(MPI_COMM_WORLD, &size);

    /* get the command line arguments and broadcast */
    if (rank == 0) {
        if (argc == 3) {
            n_x = atol(argv[1]);
            n_y = atol(argv[2]);
        }
    }
    MPI_Bcast(&n_x, 1, MPI_LONG, 0, MPI_COMM_WORLD);
    MPI_Bcast(&n_y, 1, MPI_LONG, 0, MPI_COMM_WORLD);
    data_dims[0] = n_x;
    data_dims[1] = n_y;

    /* setup hyperslab parameters */
    count[0] = data_dims[0]/size;
    count[1] = data_dims[1];
    offset[0] = rank*count[0];
    offset[1] = 0;

    /* prepare data */
    data = (int *) malloc(data_dims[1]*sizeof(int));
    if (!data) {
        fprintf(stderr, "error: can not allocate memory\n");
        MPI_Abort(MPI_COMM_WORLD, 1);
    }

    /* HDF5 file access setup */
    plist_id = H5Pcreate(H5P_FILE_ACCESS);
    H5Pset_fapl_mpio(plist_id, MPI_COMM_WORLD, info);
    file_id = H5Fcreate("test.h5", H5F_ACC_TRUNC, H5P_DEFAULT, plist_id);
    H5Pclose(plist_id);

    /* create dataset */
    filespace = H5Screate_simple(data_rank, data_dims, NULL);
    dset_id = H5Dcreate(file_id, "my_data", H5T_NATIVE_INT, filespace,
                        H5P_DEFAULT, H5P_DEFAULT, H5P_DEFAULT);

    /* create property list for write */
    plist_id = H5Pcreate(H5P_DATASET_XFER);
    H5Pset_dxpl_mpio(plist_id, H5FD_MPIO_COLLECTIVE);

    /* iterate over the rows */
    write_count[0] = 1;
    write_count[1] = count[1];
    memspace = H5Screate_simple(data_rank, write_count, NULL);
    write_offset[1] = offset[1];
    for (i = 0; i < count[0]; i++) {
        write_offset[0] = offset[0] + i;
        for (j = 0; j < count[1]; j++) {
            data[j] = 100*rank +i*count[1] + i;
        }

        /* create hyperslab */
        H5Sselect_hyperslab(filespace, H5S_SELECT_SET,
                            write_offset, NULL, write_count, NULL);

        status = H5Dwrite(dset_id, H5T_NATIVE_INT, memspace, filespace,
                          plist_id, data);
    }

    /* close HDF5 entities */
    H5Dclose(dset_id);
    H5Sclose(filespace);
    H5Sclose(memspace);
    H5Pclose(plist_id);
    H5Fclose(file_id);

    /* MPI finalization */
    MPI_Finalize();
    return EXIT_SUCCESS;
}

