#include <mpi.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define TAG 17

void clear_buff(int *buff, int n);

int main(int argc, char *argv[]) {
    int nr_msgs = 10;
    int msg_size = 1;
    int *send_buff, *recv_buff;
    int rank, size;
    MPI_Init(NULL, NULL);
    MPI_Comm_rank(MPI_COMM_WORLD, &rank);
    MPI_Comm_size(MPI_COMM_WORLD, &size);
    if (size != 2) {
        fprintf(stderr, "# error: only two can play ping-pong, run with two processes\n");
        MPI_Abort(MPI_COMM_WORLD, EXIT_FAILURE);
    }
    if (argc > 1) {
        nr_msgs = atoi(argv[1]);
    }
    if (argc > 2) {
        msg_size = atoi(argv[2]);
    }
    MPI_Bcast(&nr_msgs, 1, MPI_INT, 0, MPI_COMM_WORLD);
    MPI_Bcast(&msg_size, 1, MPI_INT, 0, MPI_COMM_WORLD);
    if ((send_buff = (int *) malloc(sizeof(int)*msg_size)) == NULL) {
        fprintf(stderr, "# error: can create send buffer\n");
        MPI_Abort(MPI_COMM_WORLD, EXIT_FAILURE);
    }
    for (int i = 0; i < msg_size; ++i) {
        send_buff[i] = i;
    }
    if ((recv_buff = (int *) malloc(sizeof(int)*msg_size)) == NULL) {
        fprintf(stderr, "# error: can create receive buffer\n");
        MPI_Abort(MPI_COMM_WORLD, EXIT_FAILURE);
    }
    double start_time = MPI_Wtime();
    for (int msg_nr = 0; msg_nr < nr_msgs; ++msg_nr) {
#ifdef CHECK
        clear_buff(recv_buff, msg_size);
#endif
        if (rank == 0) {
            MPI_Ssend(send_buff, msg_size, MPI_INT, 1, TAG, MPI_COMM_WORLD);
        } else {
            MPI_Recv(recv_buff, msg_size, MPI_INT, 0, TAG, MPI_COMM_WORLD, MPI_STATUS_IGNORE);
#ifdef CHECK
            if (memcmp(send_buff, recv_buff, msg_size) != 0) {
                fprintf(stderr, "# error: messages do not match\n");
            }
#endif
        }
        if (rank == 0) {
            MPI_Recv(recv_buff, msg_size, MPI_INT, 1, TAG, MPI_COMM_WORLD, MPI_STATUS_IGNORE);
#ifdef CHECK
            if (memcmp(send_buff, recv_buff, msg_size) != 0) {
                fprintf(stderr, "# error: messages do not match\n");
            }
#endif
        } else {
            MPI_Ssend(send_buff, msg_size, MPI_INT, 0, TAG, MPI_COMM_WORLD);
        }
    }
    double end_time = MPI_Wtime();
    printf("process %d: %.1lf\n", rank, 1.0e6*(end_time - start_time)/(2*nr_msgs));
    MPI_Finalize();
    return 0;
}

void clear_buff(int *buff, int n) {
    for (int i = 0; i < n; ++i) {
        buff[i] = -1;
    }
}
