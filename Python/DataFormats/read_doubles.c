#include <err.h>
#include <math.h>
#include <stdio.h>
#include <stdlib.h>

int main(int argc, char *argv[]) {
    char *fileName;
    int i = 0;
    double number;
    FILE *fp;
    if (argc == 1)
        errx(EXIT_FAILURE, "no input file name given");
    fileName = argv[1];
    if ((fp = fopen(fileName, "rb")) == NULL)
        err(EXIT_FAILURE, "can't open file '%s'", fileName);
    while (fread(&number, sizeof(double), 1, fp))
        printf("%lf == %lf\n", number, sqrt((double) i++));
    fclose(fp);
    return EXIT_SUCCESS;
}

