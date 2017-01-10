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
    if (argc > 1)       
        nr_iters = atol(argv[2]);
    for (iter_nr = 0; iter_nr < nr_iters; iter_nr++) {
        c_read = getchar();
        if (c_read == EOF)
            errx(FILE_TOO_SHORT, "file too short, got  %ld, should be %ld",
                    iter_nr, nr_iters);
        if (c != c_read)
            errx(UNEXPECTED_CHAR, "unexpected '%c', should be '%c'",
                    c_read, c);
        putchar(c_read);
        if (++c > '9')
            c = '0';
    }
    c_read = getchar();
    if (c_read != EOF)
        errx(FILE_TOO_LONG, "file too long, should be %ld", nr_iters);
    return EXIT_SUCCESS;
}
