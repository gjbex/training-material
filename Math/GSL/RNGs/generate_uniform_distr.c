#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <gsl/gsl_rng.h>
#include <gsl/gsl_randist.h>

int main(int argc, char *argv[]) {
    unsigned long seed = 1234;
    int n = 10;
    if (argc > 1)
        n = atoi(argv[1]);
    gsl_rng_env_setup();
    gsl_rng *rng = gsl_rng_alloc(gsl_rng_mt19937);
    gsl_rng_set(rng, seed);
    for (int i = 0; i < n; i++) {
        double x = gsl_rng_uniform(rng);
        printf("%.12f\n", x);
    }
    gsl_rng_free(rng);
    return EXIT_SUCCESS;
}

