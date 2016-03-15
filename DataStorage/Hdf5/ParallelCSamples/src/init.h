#ifndef INIT_HDR
#define INIT_HDR

#include <mpi.h>

#include <consts.h>

void get_mode(int argc, char *argv[], MPI_Comm comm, int *mode);
void get_file_name(int argc, char *argv[], MPI_Comm comm,
                   char file_name[MAX_STR_LEN]);
void get_dims_from_cl(int argc, char *argv[], MPI_Comm comm,
                      int dims[RANK]);
void get_dims_from_file(char file_name[MAX_STR_LEN], MPI_Comm comm,
                        int dims[RANK]);

#endif

