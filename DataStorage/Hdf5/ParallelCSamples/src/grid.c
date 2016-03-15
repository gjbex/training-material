#include <math.h>
#include <stdlib.h>

#include "grid.h"

void partition_grid(int nr_points, int nr_procs, int proc,
                    int *offset, int *size) {
    int rem = nr_points % nr_procs;
    if (proc < rem) {
        *size = nr_points/nr_procs + 1;
        *offset = proc*(*size);
    } else {
        *size = nr_points/nr_procs;
        *offset = rem*(*size + 1) + (proc - rem)*(*size);
    }
}

void init_grid(int nr_points, int offset, int size, float **grid) {
    if ((*grid = (float *) malloc(size*sizeof(float))) != NULL) {
        int i;
        float x_delta = 1.0/nr_points;
        float x = offset*x_delta;
        for (i = 0; i < size; i++) {
            (*grid)[i] = x;
            x += x_delta;
        }
    }
}

void init_2d_field(int size[2], float *grid[2], float **field) {
    const int nr_points = size[0]*size[1];
    int i, j;
    if ((*field = (float *) malloc(nr_points*sizeof(float))) != NULL) {
        for (i = 0; i < size[0]; i++) {
            float x = grid[0][i];
            for (j = 0; j < size[1]; j++) {
                float y = grid[1][j];
                int idx = i*size[1] + j;
                (*field)[idx] = exp(-(x*x + y*y));
            }
        }
    }
}

void init_3d_field(int size[3], float *grid[3], float **field) {
    const int nr_points = size[0]*size[1]*size[2];
    int i, j, k;
    if ((*field = (float *) malloc(nr_points*sizeof(float))) != NULL) {
        for (i = 0; i < size[0]; i++) {
            float x = grid[0][i];
            for (j = 0; j < size[1]; j++) {
                float y = grid[1][j];
                for (k = 0; k < size[2]; k++) {
                    float z = grid[2][k];
                    int idx = i*size[1]*size[2] + j*size[2] + k;
                    (*field)[idx] = exp(-(x*x + y*y + z*z));
                }
            }
        }
    }
}

