#ifndef GRID_HDR
#define GRID_HDR

void partition_grid(int nr_points, int nr_procs, int proc,
                    int *offset, int *size);
void init_grid(int nr_points, int offset, int size, float **grid);
void init_2d_field(int size[2], float *grid[2], float **field);
void init_3d_field(int size[3], float *grid[3], float **field);

#endif

