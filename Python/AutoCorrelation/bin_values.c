#include <err.h>
#include <stdio.h>
#include <stdlib.h>
#include <math.h>

int main(int argc, char * argv[]) {
    int index, nrBins = 10, nrX = 0;
    double x, *bins;
    if (argc > 1) nrBins = atoi(argv[1]);
    if ((bins = (double *) malloc(nrBins*sizeof(double))) == NULL) {
        errx(EXIT_FAILURE, "can not allocate bins");
    }
    for (index = 0; index < nrBins; index++) bins[index] = 0.0;
    while (scanf("%lf", &x)) {
        nrX++;
        index = (int) floor(nrBins*x);
        bins[index] += 1.0;
        if (feof(stdin)) break;
    }
    for (index = 0; index < nrBins; index++) {
        printf("%.2lf\t%.3lf\n", ((double) index)/nrBins, bins[index]/nrX);
    }
    return EXIT_SUCCESS;
}

