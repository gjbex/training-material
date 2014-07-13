#ifndef CHECKPOINT_HDR
#define CHECKPOINT_HDR

#include <hdf5.h>

void save_grid(hid_t file_id, char name[2], int total_size,
               int offset, int size, float *grid);
void read_grid(hid_t file_id, char name[2], int total_size,
               int offset, int size, float **grid);
void save_2d_field(hid_t file_id, char name[], int total_size[2],
                   int offset[2], int size[2], float *field, int mode);
void read_2d_field(hid_t file_id, char name[], int total_size[2],
                   int offset[2], int size[2], float **field);

#endif

