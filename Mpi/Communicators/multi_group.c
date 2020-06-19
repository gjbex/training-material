/*
 * Example of using ranges.  The aim is to divide the processes into two groups
 * according to their rank.
 *
 * rank:   0  1  3  4  5  6  7  8  9
 * group:  1  1  2  2  1  1  2  2  1
 */
#include <stdio.h>
#include <stdlib.h>
#include <mpi.h>

int main() {
    MPI_Init(NULL, NULL);
    int my_rank;
    MPI_Comm_rank(MPI_COMM_WORLD, &my_rank);
    int my_size;
    MPI_Comm_size(MPI_COMM_WORLD, &my_size);
    int group_nr;
    int ranges[2][3];
    if (my_rank % 4 == 0 || (my_rank - 1) % 4 == 0) {
        ranges[0][0] = 0;
        ranges[1][0] = 1;
        group_nr = 1;
    } else {
        ranges[0][0] = 2;
        ranges[1][0] = 3;
        group_nr = 2;
    }
    ranges[0][1] = my_size - 1;
    ranges[0][2] = 4;
    ranges[1][1] = my_size - 1;
    ranges[1][2] = 4;
    printf("%d: (%d, %d, %d), (%d, %d, %d)\n", my_rank,
            ranges[0][0], ranges[0][1], ranges[0][2],
            ranges[1][0], ranges[1][1], ranges[1][2]);
    MPI_Barrier(MPI_COMM_WORLD);
    MPI_Group world_group;
    MPI_Comm_group(MPI_COMM_WORLD, &world_group);
    MPI_Group group;
    MPI_Group_range_incl(world_group, 2, ranges, &group);
    int new_rank;
    int new_size;
    MPI_Comm new_comm;
    MPI_Comm_create(MPI_COMM_WORLD, group, &new_comm);
    MPI_Comm_rank(new_comm, &new_rank);
    MPI_Comm_size(new_comm, &new_size);
    printf("%d, group %d: (%d, %d)\n", my_rank, group_nr, new_rank, new_size);
    MPI_Finalize();
    return 0;
}
