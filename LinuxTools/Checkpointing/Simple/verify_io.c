#include <err.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define UNEXPECTED_CHAR 10
#define FILE_TOO_SHORT 11
#define FILE_TOO_LONG 12

int main(int argc, char *argv[]) {
    char c = '0', c_read;
    long iter_nr, nr_iters = 10;
    char filename[1024] = "dump.txt";
    FILE *fp;
    if (argc > 1)
        strncpy(filename, argv[1], 1023);
    if (argc > 2)       
        nr_iters = atol(argv[2]);
    fp = fopen(filename, "r");
    if (fp == NULL)
        err(EXIT_FAILURE, "problem opening file '%s'", filename);
    for (iter_nr = 0; iter_nr < nr_iters; iter_nr++) {
        c_read = fgetc(fp);
        if (feof(fp))
            errx(FILE_TOO_SHORT, "file too short, got  %ld, should be %d",
                    iter_nr, nr_iters);
        if (c != c_read)
            errx(UNEXPECTED_CHAR, "unexpected '%c', should be '%c'",
                    c_read, c);
        if (++c > '9')
            c = '0';
    }
    c_read = fgetc(fp);
    if (!feof(fp))
        errx(FILE_TOO_LONG, "file too long, should be %d", nr_iters);
    fclose(fp);
    return EXIT_SUCCESS;
}
