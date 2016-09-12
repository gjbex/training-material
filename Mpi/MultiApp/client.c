#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <mpi.h>

#define MAX_LEN 80
#define TAG 11

int main(int argc, char *argv[]) {
    int rank, size, inter_comm_size;
    char port_name[MPI_MAX_PORT_NAME];
    char buff[MAX_LEN] = "client greetings!";
    char port_filename[MAX_LEN] = "port_name.txt";
    char hostnaem[MAX_LEN];
    int hostname_len = 0;
    FILE *fp;
    MPI_Comm inter_comm;
    MPI_Status status;

    /* usual MPI setup */
    MPI_Init(NULL, NULL);
    MPI_Comm_rank(MPI_COMM_WORLD, &rank);
    MPI_Comm_size(MPI_COMM_WORLD, &size);
    if (rank == 0)
        printf("%s: %d processes\n", argv[0], size);

    /* determine and print hostname */
    if (rank == 0) {
        MPI_Get_processor_name(hostname, &hostname_len);
        printf("client running on %s\n", hostname);
    }

    /* read port name file */
    if ((fp = fopen(port_filename, "r")) == NULL) {
        fprintf(stderr, "### error: can't read port name file\n");
        MPI_Abort(MPI_COMM_WORLD, EXIT_FAILURE);
    }
    fread(port_name, sizeof(char), MPI_MAX_PORT_NAME, fp);
    fclose(fp);

    /* establish connection to server application */
    if (rank == 0)
        printf("connecting to port: %s\n", port_name);
    MPI_Comm_connect(port_name, MPI_INFO_NULL, 0, MPI_COMM_WORLD,
                     &inter_comm);

    /* some feedback on new communicator */
    MPI_Comm_size(inter_comm, &inter_comm_size);
    if (rank == 0)
        printf("%s intercommunicator size: %d\n", argv[0], inter_comm_size);

    /* send a message to server application */
    if (rank == 0) {
        MPI_Send(buff, MAX_LEN, MPI_CHAR, 0, TAG, inter_comm);
        printf("client sent greeting '%s'\n", buff);
        MPI_Recv(buff, MAX_LEN, MPI_CHAR, MPI_ANY_SOURCE, MPI_ANY_TAG,
                 inter_comm, &status);
        printf("client received '%s'\n", buff);
    }
    MPI_Bcast(buff, MAX_LEN, MPI_CHAR, 0, MPI_COMM_WORLD);
    printf("client rank %d received '%s'\n", rank, buff);

    /* clean up */
    MPI_Comm_free(&inter_comm);
    MPI_Finalize();

    return EXIT_SUCCESS;
}

