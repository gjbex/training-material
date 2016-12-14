#include <stdio.h>
#include <stdlib.h>

#include <gsl/gsl_vector.h>
#include <gsl/gsl_multimin.h>

typedef struct {
    gsl_vector *alpha, *center;
    double offset;
} Params;

/*
 * Function implements a 2-D parabola centered on center, with minimum
 * at offset.
 * */
double parabola(const gsl_vector *v, void *params) {
    double x = gsl_vector_get(v, 0);
    double y = gsl_vector_get(v, 1);
    Params *p = (Params *) params;
    double a = gsl_vector_get(p->alpha, 0);
    double b = gsl_vector_get(p->alpha, 1);
    double c = p->offset;
    x -= gsl_vector_get(p->center, 0);
    y -= gsl_vector_get(p->center, 1);
    return a*x*x + b*y*y + c;
}

int main(int argc, char *argv[]) {
    const int nr_dims = 2, nr_iters = 100;
    /* Use Nelder & Mead simplex method */
    const gsl_multimin_fminimizer_type *T = gsl_multimin_fminimizer_nmsimplex2;
    gsl_multimin_fminimizer *multimin;
    gsl_multimin_function f;
    gsl_vector *x, *step_size;
    Params params;
    int iter_nr = 0, status;
    double size;

    /* Initialize the parameters */
    params.alpha = gsl_vector_alloc(nr_dims);
    gsl_vector_set(params.alpha, 0, 1.0);
    gsl_vector_set(params.alpha, 1, 2.0);
    params.center = gsl_vector_alloc(nr_dims);
    gsl_vector_set(params.center, 0, 1.5);
    gsl_vector_set(params.center, 1, -0.5);
    params.offset = 3.4;
    f.n = nr_dims;
    f.f = parabola;
    f.params = &params;

    /* Initiallize the initial position */
    x = gsl_vector_alloc(nr_dims);
    gsl_vector_set(x, 0, 2.3);
    gsl_vector_set(x, 1, -1.5);

    /* Initialize the simplex step sizes */
    step_size = gsl_vector_alloc(nr_dims);
    gsl_vector_set_all(step_size, 1.0);

    /* Initialize the minimizer */
    multimin = gsl_multimin_fminimizer_alloc(T, 2);
    gsl_multimin_fminimizer_set(multimin, &f, x, step_size);

    /* Do the iterations until success, or the maximum number of iterations
     * is exceeded. */
    do {
        iter_nr++;
        /* Do an iteration step */
        status = gsl_multimin_fminimizer_iterate(multimin);
        if (status)
            break;
        /* Determine the step size to use a a stopping criterion */
        size = gsl_multimin_fminimizer_size(multimin);
        status = gsl_multimin_test_size(size, 1.0e-4);
        if (status == GSL_SUCCESS) {
            printf("Minimum:\n");
            printf("%4d: f(%.5f, %.5f) = %.5f, last step size = %.5f\n",
                   iter_nr,
                   gsl_vector_get(multimin->x, 0),
                   gsl_vector_get(multimin->x, 1),
                   multimin->fval,
                   size);
            printf("Expected:\n");
            printf("      f(%.5f, %.5f) = %.5f\n",
                   gsl_vector_get(params.center, 0),
                   gsl_vector_get(params.center, 1),
                   params.offset);
        } else {
            fprintf(stderr, "%4d: f(%.5f, %.5f) = %.5f, step size = %.5f\n",
                    iter_nr,
                    gsl_vector_get(multimin->x, 0),
                    gsl_vector_get(multimin->x, 1),
                    multimin->fval,
                    size);
        }
    } while (status == GSL_CONTINUE && iter_nr < nr_iters);

    /* Free everything that was allocated */
    gsl_multimin_fminimizer_free(multimin);
    gsl_vector_free(x);
    gsl_vector_free(step_size);
    gsl_vector_free(params.alpha);
    gsl_vector_free(params.center);
    return EXIT_SUCCESS;
}
