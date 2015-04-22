#include <err.h>
#include <math.h>
#include <stdio.h>
#include <stdlib.h>

int main(int argc, char *argv[]) {
    FILE *fp;
    int i, nr_data, dummy;
    double x, y;

    if (argc < 2)
        errx(EXIT_FAILURE, "#error: no file name specified");
    if ((fp = fopen(argv[1], "rb")) == NULL)
        err(EXIT_FAILURE, "#error");
    if (!fread(&nr_data, sizeof(nr_data), 1, fp))
        errx(EXIT_FAILURE, "#error: read failed");
    printf("nr = %d\n", nr_data);
    for (i = 0; i < nr_data; i++) {
        if (!fread(&dummy, sizeof(nr_data), 1, fp))
            errx(EXIT_FAILURE, "#error: read failed");
        if (!fread(&x, sizeof(x), 1, fp))
            errx(EXIT_FAILURE, "#error: read failed");
        if (!fread(&y, sizeof(y), 1, fp))
            errx(EXIT_FAILURE, "#error: read failed");
        printf("%lf\t%lf\t%le\n", x, y, fabs(y - sqrt(x))/sqrt(x));
    }
    fclose(fp);

    return EXIT_SUCCESS;
}
