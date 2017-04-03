#include <err.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>

int main(int argc, char *argv[]) {
    char c = '0';
    long iter_nr, nr_iters = 10;
    unsigned int sleeptime = 1;
    char filename[1024] = "dump.txt";
    FILE *fp;
    if (argc > 1)
        strncpy(filename, argv[1], 1023);
    if (argc > 2)       
        nr_iters = atol(argv[2]);
    if (argc > 3)
        sleeptime = (unsigned int) atoi(argv[3]);
    fp = fopen(filename, "w");
    if (fp == NULL)
        err(EXIT_FAILURE, "problem opening file '%s'", filename);
    for (iter_nr = 0; iter_nr < nr_iters; iter_nr++) {
        fputc(c++, fp);
        if (c > '9')
            c = '0';
        if (iter_nr % 100 == 0)
            sleep(sleeptime);
    }
    fclose(fp);
    return EXIT_SUCCESS;
}
