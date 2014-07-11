#include <err.h>
#include <math.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include <netcdf.h>

#define MAX_STR_LEN 1024
#define N_DIMS 3

float *create_data(int dims[N_DIMS]);

int main(int argc, char *argv[]) {
    const int default_ooints = 10;
    int nr_points = default_ooints;
    int dims[N_DIMS];
    float *data = NULL;
    int nc_id, dim_ids[N_DIMS], var_id;
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

/* define variable */
    if ((ret_val = nc_def_var(nc_id, "value", NC_FLOAT,
                              N_DIMS, dim_ids, &var_id)) != 0) {
        errx(ret_val, "variable value definition failed");
    }

/* all metadata has been defined, end definition mode */
    if ((ret_val = nc_enddef(nc_id)) != 0) {
        errx(ret_val, "end defintition mode failed");
    }

/* create data */
    data = create_data(dims);

/* write data to NetCDF file */
    if ((ret_val = nc_put_var_float(nc_id, var_id, &(data[0]))) != 0) {
        errx(ret_val, "writing data failed");
    }

/* free data */
    free(data);

/* close file */
    if ((ret_val = nc_close(nc_id)) != 0) {
        errx(ret_val, "file close failed");
    }

    return EXIT_SUCCESS;
}

float *create_data(int dims[N_DIMS]) {
    const int n = dims[0]*dims[1]*dims[2];
    int i, j, k;
    float *data;
    const float min = -1.0, max = 1.0;
    float delta = (max - min)/n;
    float x, y, z;
    if ((data = (float *) malloc(n*sizeof(float))) == NULL) {
        errx(EXIT_FAILURE, "can not allocate data");
    }
    x = min;
    for (i = 0; i < dims[0]; i++) {
        y = min;
        for (j = 0; j < dims[1]; j++) {
            z = min;
            for (k = 0; k < dims[2]; k++) {
                int idx = i*dims[1]*dims[2] + j*dims[2] + k;
                data[idx] = exp(-(x*x + y*y + z*z));
                z += delta;
            }
            y += delta;
        }
        x += delta;
    }
    return data;
}

