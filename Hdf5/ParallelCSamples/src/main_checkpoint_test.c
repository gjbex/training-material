#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <mpi.h>
#include <hdf5.h>

#include "consts.h"
#include "init.h"
#include "grid.h"
#include "checkpoint.h"

#define IS_DEBUG 1

void recompute(float *field, float *grid[RANK], int size[RANK]);

int main(int argc, char *argv[]) {
    int comm_rank, comm_size;
    int mode = NO_MODE;
    /* dims: dimension of the complete grid
     * dims_cart: dimensions of the carthesian topology
     * is_periodic: whether carthesian topology is periodic
     * coord_cart: process coordinates in carthesian topology
     * offset: offset value for process in grid
     * size: local grid size */
    int dims[RANK], dims_cart[RANK] = {0, 0},
        is_periodic[RANK] = {FALSE, FALSE}, coord_cart[RANK],
        offset[RANK], size[RANK];
    int can_reorder = TRUE;
    MPI_Comm comm_cart;
    MPI_Info info = MPI_INFO_NULL;
    char file_name[MAX_STR_LEN];
    float *grid[RANK], *field;
    hid_t file_id, plist_id;

    /* Initialize MPI and retrieve size and rank */
    MPI_Init(&argc, &argv);
    MPI_Comm_size(MPI_COMM_WORLD, &comm_size);
    MPI_Comm_rank(MPI_COMM_WORLD, &comm_rank);

    /* determine and broadcast the mode, either new or restart */
    get_mode(argc, argv, MPI_COMM_WORLD, &mode);
    if (IS_DEBUG) {
        fprintf(stderr, "rank %d: mode %d\n", comm_rank, mode);
    }

    /* determine and broadcast file name */
    get_file_name(argc, argv, MPI_COMM_WORLD, file_name);
    if (IS_DEBUG) {
        fprintf(stderr, "rank %d: file '%s'\n", comm_rank, file_name);
    }

    /* determine and broadcast dimensions */
    if (NEW_MODE == mode) {
        get_dims_from_cl(argc, argv, MPI_COMM_WORLD, dims);
    } else if (RESTART_MODE == mode) {
        get_dims_from_file(file_name, MPI_COMM_WORLD, dims);
    }
    if (IS_DEBUG) {
        fprintf(stderr, "rank %d: dims %d x %d\n", comm_rank,
                dims[0], dims[1]);
    }

    /* create 2D carthesian topology, retrieve new rank, and
     * cartheisan coordinates for process */
    MPI_Dims_create(comm_size, RANK, dims_cart);
    MPI_Cart_create(MPI_COMM_WORLD, RANK, dims_cart, is_periodic,
                    can_reorder, &comm_cart);
    MPI_Comm_rank(comm_cart, &comm_rank);
    MPI_Cart_coords(comm_cart, comm_rank, RANK, coord_cart);
    if (IS_DEBUG) {
        fprintf(stderr, "rank %d: (%d, %d)\n", comm_rank,
                coord_cart[0], coord_cart[1]);
    }

    /* determine matrix offset and size */
    partition_grid(dims[0], dims_cart[0], coord_cart[0],
                   &(offset[0]), &(size[0]));
    partition_grid(dims[1], dims_cart[1], coord_cart[1],
                   &(offset[1]), &(size[1]));
    if (IS_DEBUG) {
        fprintf(stderr, "rank %d: (%d, %d) -> (%d, %d)\n", comm_rank,
                offset[0], offset[1],
                offset[0] + size[0] - 1, offset[1] + size[1] - 1);
    }

    /* initialize grid, compute and save when mode is 'new', read from
     * file if mode is 'restart' */
    if (NEW_MODE == mode) {
        /* compute grid */
        init_grid(dims[0], offset[0], size[0], &(grid[0]));
        init_grid(dims[1], offset[1], size[1], &(grid[1]));
        if (grid[0] == NULL || grid[1] == NULL) {
            fprintf(stderr, "# error: can not allocate grid\n");
            MPI_Abort(comm_cart, EXIT_FAILURE);
        }
        /* open HDF5 file to save grid, overwrite file if it exists */
        plist_id = H5Pcreate(H5P_FILE_ACCESS);
        H5Pset_fapl_mpio(plist_id, comm_cart, info);
        file_id = H5Fcreate(file_name, H5F_ACC_TRUNC, H5P_DEFAULT,
                            plist_id);
        H5Pclose(plist_id);
        /* save grid points to HDF5 file */
        save_grid(file_id, "x", dims[0], offset[0], size[0], grid[0]);
        save_grid(file_id, "y", dims[1], offset[1], size[1], grid[1]);
        /* close HDF5 file */
        H5Fclose(file_id);
    } else if (RESTART_MODE == mode) {
        /* open HDF5 file to read grid */
        plist_id = H5Pcreate(H5P_FILE_ACCESS);
        H5Pset_fapl_mpio(plist_id, comm_cart, info);
        file_id = H5Fopen(file_name, H5F_ACC_RDONLY, plist_id);
        H5Pclose(plist_id);
        /* read grid points from HDF5 file */
        read_grid(file_id, "x", dims[0], offset[0], size[0], &(grid[0]));
        read_grid(file_id, "y", dims[1], offset[1], size[1], &(grid[1]));
        /* close HDF5 file */
        H5Fclose(file_id);
    }
    if (IS_DEBUG) {
        fprintf(stderr, "rank %d: %.3f:%.3f:%.3f, %.3f:%.3f:%.3f\n",
                comm_rank,
                grid[0][0], grid[0][1] - grid[0][0], grid[0][size[0]-1],
                grid[1][0], grid[1][1] - grid[1][0], grid[1][size[1]-1]);
    }

    /* initialize field values, either compute in new mode, or
     * read from file in restart mode */
    if (NEW_MODE == mode) {
        /* compute field */
        init_2d_field(size, grid, &field);
        if (field == NULL) {
            fprintf(stderr, "# error: can not allocate field\n");
            MPI_Abort(comm_cart, EXIT_FAILURE);
        }
        /* open HDF5 file to save field */
        plist_id = H5Pcreate(H5P_FILE_ACCESS);
        H5Pset_fapl_mpio(plist_id, comm_cart, info);
        file_id = H5Fopen(file_name, H5F_ACC_RDWR, plist_id);
        H5Pclose(plist_id);
        /* save grid points to HDF5 file */
        save_2d_field(file_id, "field", dims, offset, size, field, mode);
        /* close HDF5 file */
        H5Fclose(file_id);
    } else if (RESTART_MODE == mode) {
        /* open HDF5 file to read field */
        plist_id = H5Pcreate(H5P_FILE_ACCESS);
        H5Pset_fapl_mpio(plist_id, comm_cart, info);
        file_id = H5Fopen(file_name, H5F_ACC_RDONLY, plist_id);
        H5Pclose(plist_id);
        /* save grid points to HDF5 file */
        read_2d_field(file_id, "field", dims, offset, size, &field);
        /* close HDF5 file */
        H5Fclose(file_id);
    }

    /* recompute, whatever the mode */
    if (IS_DEBUG) {
        fprintf(stderr, "rank %d: old field = %.6f\n",
                comm_rank, field[0]);
    }
    recompute(field, grid, size);
    if (IS_DEBUG) {
        fprintf(stderr, "rank %d: new field = %.6f\n",
                comm_rank, field[0]);
    }
    /* open HDF5 file to save field */
    plist_id = H5Pcreate(H5P_FILE_ACCESS);
    H5Pset_fapl_mpio(plist_id, comm_cart, info);
    file_id = H5Fopen(file_name, H5F_ACC_RDWR, plist_id);
    H5Pclose(plist_id);
    /* save grid points to HDF5 file */
    save_2d_field(file_id, "field", dims, offset, size, field,
                  RESTART_MODE);
    /* close HDF5 file */
    H5Fclose(file_id);

    /* free allocated memory */
    free(grid[0]);
    free(grid[1]);
    free(field);

    /* finalize MPI */
    MPI_Finalize();

    return EXIT_SUCCESS;
}

void recompute(float *field, float *grid[RANK], int size[RANK]) {
    int i, j;
    for (i = 0; i < size[0]; i++) {
        float x = grid[0][i];
        for (j = 0; j < size[1]; j++) {
            float y = grid[1][j];
            int idx = i*size[1] + j;
            field[idx] *= exp(-0.1*(x*x + y*y));
        }
    }
}

