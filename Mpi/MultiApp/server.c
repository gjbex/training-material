#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <mpi.h>

#define MAX_LEN 80
#define TAG 11

int main(int argc, char *argv[]) {
    int rank, size, inter_comm_size;
    char port_name[MPI_MAX_PORT_NAME];
    char buff[MAX_LEN];
    char port_filename[MAX_LEN] = "port_name.txt";
    char hostname[MAX_LEN];
    int hostname_len = 0;
    MPI_Comm inter_comm;
    MPI_Status status;

    /* usual MPI setup */
    MPI_Init(NULL, NULL);
    MPI_Comm_rank(MPI_COMM_WORLD, &rank);
    MPI_Comm_size(MPI_COMM_WORLD, &size);
    if (rank == 0)
        printf("%s: %d processes\n", argv[0], size);

    /* determine and print hostname */
    MPI_Get_processor_name(hostname, &hostname_len);
    printf("%s process %d running on %s\n", argv[0], rank, hostname);

    /* open a port for communicaiton from a client */
    MPI_Open_port(MPI_INFO_NULL, port_name);

    /* write the port name file */
    if (rank == 0) {
        FILE *fp;
        if ((fp = fopen(port_filename, "w")) == NULL) {
            fprintf(stderr, "### error: can't write port name file\n");
            MPI_Abort(MPI_COMM_WORLD, EXIT_FAILURE);
        }
        fprintf(fp, "%s\n", port_name);
        fclose(fp);
        printf("server on port: %s\n", port_name);
    }

    /* start accepting communication on the port */
    MPI_Comm_accept(port_name, MPI_INFO_NULL, 0, MPI_COMM_WORLD,
                    &inter_comm);

    /* provide some feedback on the new communicator */
    MPI_Comm_size(inter_comm, &inter_comm_size);
    if (rank == 0)
        printf("%s intercommunicator size: %d\n", argv[0], inter_comm_size);

    /* receive a message from the client and print it */
    if (rank == 0) {
        MPI_Recv(buff, MAX_LEN, MPI_CHAR, MPI_ANY_SOURCE, MPI_ANY_TAG,
                 inter_comm, &status);
    }
    MPI_Bcast(buff, MAX_LEN, MPI_CHAR, 0, MPI_COMM_WORLD);
    printf("server rank %d received '%s'\n", rank, buff);

    if (rank == 0) {
        strncpy(buff, "server greetings!", MAX_LEN);
        MPI_Send(buff, MAX_LEN, MPI_CHAR, 0, TAG, inter_comm);
        printf("server sent greeting '%s'\n", buff);
    }

    /* clean up */
    MPI_Comm_free(&inter_comm);
    MPI_Close_port(port_name);
    MPI_Finalize();

    return EXIT_SUCCESS;
}
