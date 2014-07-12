#ifndef GRID_HDR
#define GRID_HDR

float **create_uniform_grid(int dims[], int n_dims);
float **create_quadratic_grid(int dims[], int n_dims);
void free_grid(float **grid, int n_dims);
float *compute_2d_data(float (*f)(float, float, void *), void *pars,
                       float **grid, int dims[]);
float *compute_3d_data(float (*f)(float, float, float, void *), void *pars,
                       float **grid, int dims[]);

#endif

