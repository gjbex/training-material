#include <err.h>
#include <math.h>
#include <stdio.h>
#include <stdlib.h>

int main(int argc, char *argv[]) {
    char *fileName;
    int i, size = 10;
    FILE *fp;
    if (argc == 1)
        errx(EXIT_FAILURE, "no output file name given");
    fileName = argv[1];
    if (argc > 2)
        size = atoi(argv[2]);    
    if ((fp = fopen(fileName, "wb")) == NULL)
        err(EXIT_FAILURE, "can't open file '%s'", fileName);
    for (i = 0; i < size; i++) {
        double number = sqrt((double) i);
        fwrite(&number, 1, sizeof(double), fp);
    }
    fclose(fp);
    return EXIT_SUCCESS;
}

