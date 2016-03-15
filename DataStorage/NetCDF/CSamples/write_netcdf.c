#include <err.h>
#include <math.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include <netcdf.h>

#include "grid.h"

#define MAX_STR_LEN 1024
#define N_DIMS 3

float gauss(float x, float y, float z, void *params);

int main(int argc, char *argv[]) {
    const int default_ooints = 10;
    int nr_points = default_ooints;
    int dims[N_DIMS];
    float **grid = NULL;
    float *data = NULL;
    int nc_id, dim_ids[N_DIMS], var_x_id, var_y_id, var_z_id, var_value_id;
    int ret_val;
    char file_name[MAX_STR_LEN];
    
/* handle command line arguments */
    if (argc >= 2) {
        strncpy(file_name, argv[1], MAX_STR_LEN);
    } else {
        errx(EXIT_FAILURE, "no file name speicified");
    }
    if (argc >= 3) {
        nr_points = atoi(argv[2]);
    }
/* set dimensions */
    dims[0] = dims[1] = dims[2] = nr_points;

/* create NetCDF file, overwrite if it exists (NC_CLOBBER */
    if ((ret_val = nc_create(file_name, NC_CLOBBER, &nc_id)) != 0) {
        errx(ret_val, "file creation failed");
    }

/* define NetCDF dimensions */
    if ((ret_val = nc_def_dim(nc_id, "x", dims[0], &(dim_ids[0]))) != 0) {
        errx(ret_val, "x dimension definition failed");
    }
    if ((ret_val = nc_def_dim(nc_id, "y", dims[1], &(dim_ids[1]))) != 0) {
        errx(ret_val, "y dimension definition failed");
    }
    if ((ret_val = nc_def_dim(nc_id, "z", dims[2], &(dim_ids[2]))) != 0) {
        errx(ret_val, "z dimension definition failed");
    }

/* define x, y, z grid variables */
    if ((ret_val = nc_def_var(nc_id, "x", NC_FLOAT,
                              1, &(dim_ids[0]), &var_x_id)) != 0) {
        errx(ret_val, "variable x definition failed");
    }
    if ((ret_val = nc_def_var(nc_id, "y", NC_FLOAT,
                              1, &(dim_ids[1]), &var_y_id)) != 0) {
        errx(ret_val, "variable y definition failed");
    }
    if ((ret_val = nc_def_var(nc_id, "z", NC_FLOAT,
                              1, &(dim_ids[2]), &var_z_id)) != 0) {
        errx(ret_val, "variable z definition failed");
    }

/* define value variable */
    if ((ret_val = nc_def_var(nc_id, "value", NC_FLOAT,
                              N_DIMS, dim_ids, &var_value_id)) != 0) {
        errx(ret_val, "variable value definition failed");
    }

/* all metadata has been defined, end definition mode */
    if ((ret_val = nc_enddef(nc_id)) != 0) {
        errx(ret_val, "end defintition mode failed");
    }

/* create grid */
    grid = create_quadratic_grid(dims, N_DIMS);

/* write x, y, z grid to NetCDF file */
    if ((ret_val = nc_put_var_float(nc_id, var_x_id, &(grid[0][0]))) != 0) {
        errx(ret_val, "writing x grid variable failed");
    }
    if ((ret_val = nc_put_var_float(nc_id, var_y_id, &(grid[1][0]))) != 0) {
        errx(ret_val, "writing y grid variable failed");
    }
    if ((ret_val = nc_put_var_float(nc_id, var_z_id, &(grid[2][0]))) != 0) {
        errx(ret_val, "writing z grid variable failed");
    }

/* create data */
    data = compute_3d_data(gauss, (void *) NULL, grid, dims);

/* write data to NetCDF file */
    if ((ret_val = nc_put_var_float(nc_id, var_value_id,
                                    &(data[0]))) != 0) {
        errx(ret_val, "writing value variable  failed");
    }

/* free data */
    free(data);

/* free grid */
    free_grid(grid, N_DIMS);

/* close file */
    if ((ret_val = nc_close(nc_id)) != 0) {
        errx(ret_val, "file close failed");
    }

    return EXIT_SUCCESS;
}

float gauss(float x, float y, float z, void *params) {
    return exp(-(x*x + y*y + z*z));
}

