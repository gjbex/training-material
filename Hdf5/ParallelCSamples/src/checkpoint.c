#include <stdlib.h>

#include "consts.h"
#include "checkpoint.h"

void save_grid(hid_t file_id, char name[2], int total_size,
               int offset, int size, float *grid) {
    const int data_rank = 1;
    hid_t mem_space, file_space, dset_id, plist_id;
    hsize_t h5_offset[data_rank], h5_size[data_rank],
            h5_total_size[data_rank];
    herr_t status;

    /* initialize HDF5 offsets and counts */
     h5_offset[0] = offset;
    h5_size[0] = size;
    h5_total_size[0] = total_size;

    /* create memory space */
    mem_space = H5Screate_simple(data_rank, h5_size, NULL);

    /* create file space, and data set */
    file_space = H5Screate_simple(data_rank, h5_total_size, NULL);
    dset_id = H5Dcreate(file_id, name, H5T_NATIVE_FLOAT, file_space,
                        H5P_DEFAULT, H5P_DEFAULT, H5P_DEFAULT);
    H5Sclose(file_space);
    
    /* create hyperslab to put the data in the required positions */
    file_space = H5Dget_space(dset_id);
    H5Sselect_hyperslab(file_space, H5S_SELECT_SET,
                        h5_offset, NULL, h5_size, NULL);

    /* create property list for write */
    plist_id = H5Pcreate(H5P_DATASET_XFER);
    H5Pset_dxpl_mpio(plist_id, H5FD_MPIO_COLLECTIVE);

    /* write data (this is a collective write) */
    status = H5Dwrite(dset_id, H5T_NATIVE_FLOAT, mem_space, file_space,
                      plist_id, grid);

    /* close HDF5 entities */
    H5Pclose(plist_id);
    H5Dclose(dset_id);
    H5Sclose(file_space);
    H5Sclose(mem_space);
}

void read_grid(hid_t file_id, char name[2], int total_size,
               int offset, int size, float **grid) {
    const int data_rank = 1;
    hid_t mem_space, file_space, dset_id, plist_id;
    hsize_t h5_offset[data_rank], h5_size[data_rank],
            h5_total_size[data_rank];
    herr_t status;

    /* allocate grid */
    if ((*grid = (float *) malloc(size*sizeof(float))) == NULL) {
        return;
    }
    /* initialize HDF5 offsets and counts */
     h5_offset[0] = offset;
    h5_size[0] = size;
    h5_total_size[0] = total_size;

    /* create memory space */
    mem_space = H5Screate_simple(data_rank, h5_size, NULL);

    /* create file space, and data set */
    file_space = H5Screate_simple(data_rank, h5_total_size, NULL);
    dset_id = H5Dopen(file_id, name, H5P_DEFAULT);
    H5Sclose(file_space);
    
    /* create hyperslab to put the data in the required positions */
    file_space = H5Dget_space(dset_id);
    H5Sselect_hyperslab(file_space, H5S_SELECT_SET,
                        h5_offset, NULL, h5_size, NULL);

    /* create property list for write */
    plist_id = H5Pcreate(H5P_DATASET_XFER);
    H5Pset_dxpl_mpio(plist_id, H5FD_MPIO_COLLECTIVE);

    /* write data (this is a collective write) */
    status = H5Dread(dset_id, H5T_NATIVE_FLOAT, mem_space, file_space,
                     plist_id, *grid);

    /* close HDF5 entities */
    H5Pclose(plist_id);
    H5Dclose(dset_id);
    H5Sclose(file_space);
    H5Sclose(mem_space);
}

void save_2d_field(hid_t file_id, char name[], int total_size[2],
                   int offset[2], int size[2], float *field, int mode) {
    const int data_rank = 2;
    hid_t mem_space, file_space, dset_id, plist_id;
    hsize_t h5_offset[data_rank], h5_size[data_rank],
            h5_total_size[data_rank];
    herr_t status;

    /* initialize HDF5 offsets and counts */
    h5_offset[0] = offset[0];
    h5_offset[1] = offset[1];
    h5_size[0] = size[0];
    h5_size[1] = size[1];
    h5_total_size[0] = total_size[0];
    h5_total_size[1] = total_size[1];

    /* create memory space */
    mem_space = H5Screate_simple(data_rank, h5_size, NULL);

    /* create file space, and data set */
    file_space = H5Screate_simple(data_rank, h5_total_size, NULL);
    if (NEW_MODE == mode) {
        dset_id = H5Dcreate(file_id, name, H5T_NATIVE_FLOAT, file_space,
                            H5P_DEFAULT, H5P_DEFAULT, H5P_DEFAULT);
    } else if (RESTART_MODE == mode) {
        dset_id = H5Dopen(file_id, name, H5P_DEFAULT);
    }
    H5Sclose(file_space);
    
    /* create hyperslab to put the data in the required positions */
    file_space = H5Dget_space(dset_id);
    H5Sselect_hyperslab(file_space, H5S_SELECT_SET,
                        h5_offset, NULL, h5_size, NULL);

    /* create property list for write */
    plist_id = H5Pcreate(H5P_DATASET_XFER);
    H5Pset_dxpl_mpio(plist_id, H5FD_MPIO_COLLECTIVE);

    /* write data (this is a collective write) */
    status = H5Dwrite(dset_id, H5T_NATIVE_FLOAT, mem_space, file_space,
                      plist_id, field);
    if (status < 0) {
        fprintf(stderr, "# error: field write failed\n");
    }

    /* close HDF5 entities */
    H5Pclose(plist_id);
    H5Dclose(dset_id);
    H5Sclose(file_space);
    H5Sclose(mem_space);
}

void read_2d_field(hid_t file_id, char name[], int total_size[2],
                   int offset[2], int size[2], float **field) {
    const int nr_points = size[0]*size[1];
    const int data_rank = 2;
    hid_t mem_space, file_space, dset_id, plist_id;
    hsize_t h5_offset[data_rank], h5_size[data_rank],
            h5_total_size[data_rank];
    herr_t status;

    /* allocate memory */
    if ((*field = (float *) malloc(nr_points*sizeof(float))) == NULL) {
        return;
    }

    /* initialize HDF5 offsets and counts */
    h5_offset[0] = offset[0];
    h5_offset[1] = offset[1];
    h5_size[0] = size[0];
    h5_size[1] = size[1];
    h5_total_size[0] = total_size[0];
    h5_total_size[1] = total_size[1];

    /* create memory space */
    mem_space = H5Screate_simple(data_rank, h5_size, NULL);

    /* create file space, and data set */
    file_space = H5Screate_simple(data_rank, h5_total_size, NULL);
    dset_id = H5Dopen(file_id, name, H5P_DEFAULT);
    H5Sclose(file_space);
    
    /* create hyperslab to put the data in the required positions */
    file_space = H5Dget_space(dset_id);
    H5Sselect_hyperslab(file_space, H5S_SELECT_SET,
                        h5_offset, NULL, h5_size, NULL);

    /* create property list for write */
    plist_id = H5Pcreate(H5P_DATASET_XFER);
    H5Pset_dxpl_mpio(plist_id, H5FD_MPIO_COLLECTIVE);

    /* write data (this is a collective write) */
    status = H5Dread(dset_id, H5T_NATIVE_FLOAT, mem_space, file_space,
                     plist_id, *field);
    if (status < 0) {
        fprintf(stderr, "# error: field read failed\n");
    }

    /* close HDF5 entities */
    H5Pclose(plist_id);
    H5Dclose(dset_id);
    H5Sclose(file_space);
    H5Sclose(mem_space);
}
