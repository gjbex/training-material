#include <err.h>
#include <stdio.h>
#include <unistd.h>

int main(int argc, char *argv[]) {
    const unsigned nr_arrays = 7;
    unsigned length, i, j;
    const double delta = 0.31;
    double value;
    FILE *fp;
    if (argc != 2)
        errx(1, "### error: expecting file name for binary output");
    if (!(fp = fopen(argv[1], "wb")))
        errx(2, "### error: can't open file '%s'", argv[1]);
    for (i = 0; i < nr_arrays; i++) { 
        value = i + 0.4;
        length = i + 5;
        fwrite(&length, sizeof(unsigned), 1, fp);
        printf("%d:", length);
        for (j = 0; j < length; j++) {
            fwrite(&value, sizeof(double), 1, fp);
            printf(" %.2lf", value);
            value += delta;
        }
        printf("\n");
    }
    fclose(fp);
    return 0;
}
