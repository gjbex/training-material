#include <err.h>
#include <stdio.h>
#include <stdlib.h>

#include <gsl/gsl_vector.h>
#include <gsl/gsl_multimin.h>

typedef struct {
    double *alpha, *center;
    double offset;
} Params;

double parabola(const gsl_vector *v, void *params) {
    double x = gsl_vector_get(v, 0);
    double y = gsl_vector_get(v, 1);
    Params *p = (Params *) params;
    double a = p->alpha[0];
    double b = p->alpha[1];
    double c = p->offset;
    x -= p->center[0];
    y -= p->center[1];
    return a*x*x + b*y*y + c;
}

int main(int argc, char *argv[]) {
    const gsl_multimin_fminimizer_type *T = gsl_multimin_fminimizer_nmsimplex2;
    gsl_multimin_fminimizer *multimin;
    gsl_multimin_function f;
    gsl_vector *x, *step_size;
    Params params;
    int iter_nr = 0, status;
    double size;
    if ((params.alpha = (double *) malloc(2*sizeof(double))) == NULL)
        errx(EXIT_FAILURE, "Can't allocate params.alpha");
    if ((params.center = (double *) malloc(2*sizeof(double))) == NULL)
        errx(EXIT_FAILURE, "Can't allocate params.center");
    params.alpha[0] = 1.0;
    params.alpha[1] = 2.0;
    params.center[0] = 1.5;
    params.center[1] = -0.5;
    params.offset = 3.4;
    f.n = 2;
    f.f = parabola;
    f.params = &params;

    x = gsl_vector_alloc(2);
    gsl_vector_set(x, 0, 2.3);
    gsl_vector_set(x, 1, -1.5);
    step_size = gsl_vector_alloc(2);
    gsl_vector_set_all(step_size, 0.1);
    multimin = gsl_multimin_fminimizer_alloc(T, 2);
    gsl_multimin_fminimizer_set(multimin, &f, x, step_size);
    do {
        iter_nr++;
        status = gsl_multimin_fminimizer_iterate(multimin);
        if (status)
            break;
        size = gsl_multimin_fminimizer_size(multimin);
        status = gsl_multimin_test_size(size, 1.0e-4);
        if (status == GSL_SUCCESS)
            printf("Minimum at:\n");
        printf("%4d: f(%.5f, %.5f) = %.5f, size = %.5f\n", iter_nr,
               gsl_vector_get(multimin->x, 0),
               gsl_vector_get(multimin->x, 1),
               multimin->fval,
               size);
    } while (status == GSL_CONTINUE && iter_nr < 100);
    gsl_multimin_fminimizer_free(multimin);
    gsl_vector_free(x);
    gsl_vector_free(step_size);
    free(params.alpha);
    free(params.center);
    return EXIT_SUCCESS;
}
