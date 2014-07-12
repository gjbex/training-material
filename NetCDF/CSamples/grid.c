#include <err.h>
#include <stdlib.h>

#include "grid.h"

float **create_uniform_grid(int dims[], int n_dims) {
    int d, i;
    float **grid;
    const float x_min = 0.0, x_max = 1.0;
    float x, x_delta;
    if ((grid = (float **) malloc(n_dims*sizeof(float *))) == NULL) {
        errx(EXIT_FAILURE, "grid allocation failed");
    }
    for (d = 0; d < n_dims; d++) {
        if ((grid[d] = (float *) malloc(dims[d]*sizeof(float))) == NULL) {
            errx(EXIT_FAILURE, "grid allocation in dimension %d failed", d);
        }
        x = x_min;
        x_delta = (x_max - x_min)/dims[d];
        for (i = 0; i < dims[d]; i++) {
            grid[d][i] = x;
            x += x_delta;
        }
    }
    return grid;
}

float **create_quadratic_grid(int dims[], int n_dims) {
    int d, i;
    float **grid;
    const float x_min = 0.0, x_max = 1.0;
    float x, x_delta;
    if ((grid = (float **) malloc(n_dims*sizeof(float *))) == NULL) {
        errx(EXIT_FAILURE, "grid allocation failed");
    }
    for (d = 0; d < n_dims; d++) {
        if ((grid[d] = (float *) malloc(dims[d]*sizeof(float))) == NULL) {
            errx(EXIT_FAILURE, "grid allocation in dimension %d failed", d);
        }
        x = x_min;
        x_delta = (x_max - x_min)/dims[d];
        for (i = 0; i < dims[d]; i++) {
            grid[d][i] = x*x;
            x += x_delta;
        }
    }
    return grid;
}

void free_grid(float **grid, int n_dims) {
    int d;
    for (d = 0; d < n_dims; d++) {
        free(grid[d]);
    }
    free(grid);
}

float *compute_2d_data(float (*f)(float, float, void *), void *pars,
                       float **grid, int dims[]) {
    const int n = dims[0]*dims[1];
    int i, j;
    float *data = NULL;
    if ((data = (float *) malloc(n*sizeof(float))) == NULL) {
        errx(EXIT_FAILURE, "data allocation failure for %d float", n);
    }
    for (i = 0; i < dims[0]; i++) {
        float x = grid[0][i];
        for (j = 0; j < dims[1]; j++) {
            float y = grid[1][j];
            int idx = i*dims[1] + j;
            data[idx] = f(x, y, pars);
        }
    }
    return data;
}

float *compute_3d_data(float (*f)(float, float, float, void *), void *pars,
                       float **grid, int dims[]) {
    const int n = dims[0]*dims[1]*dims[2];
    int i, j, k;
    float *data = NULL;
    if ((data = (float *) malloc(n*sizeof(float))) == NULL) {
        errx(EXIT_FAILURE, "data allocation failure for %d float", n);
    }
    for (i = 0; i < dims[0]; i++) {
        float x = grid[0][i];
        for (j = 0; j < dims[1]; j++) {
            float y = grid[1][j];
            for (k = 0; k < dims[2]; k++) {
                float z = grid[2][k];
                int idx = i*dims[1]*dims[2] + j*dims[2] + k;
                data[idx] = f(x, y, z, pars);
            }
        }
    }
    return data;
}

