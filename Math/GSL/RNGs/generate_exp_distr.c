#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <gsl/gsl_rng.h>
#include <gsl/gsl_randist.h>

int main(int argc, char *argv[]) {
    double mu = 1.0;
    if (argc > 1)
        mu = atof(argv[1]);
    int n = 1;
    if (argc > 2)
        n = atoi(argv[2]);
    unsigned long seed;
    if (argc > 3)
        seed = atol(argv[3]);
    else
        seed = time(NULL);
    gsl_rng_env_setup();
    gsl_rng *rng = gsl_rng_alloc(gsl_rng_default);
    gsl_rng_set(rng, seed);
    for (int i = 0; i < n; i++) {
        double x = gsl_ran_exponential(rng, mu);
        printf("%.12f\n", x);
    }
    gsl_rng_free(rng);
    return EXIT_SUCCESS;
}
