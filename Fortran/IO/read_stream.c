#include <err.h>
#include <math.h>
#include <stdio.h>
#include <stdlib.h>

int main(int argc, char *argv[]) {
    FILE *fp;
    double x, total = 0.0;

    if (argc < 2)
        errx(EXIT_FAILURE, "#error: no file name specified");
    if ((fp = fopen(argv[1], "rb")) == NULL)
        err(EXIT_FAILURE, "#error");
    while (fread(&x, sizeof(x), 1, fp)) {
        total += x;
    }
    fclose(fp);
    printf("sum = %25.15le\n", total);
    return EXIT_SUCCESS;
}
