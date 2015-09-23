#include <stdio.h>
#include <stdlib.h>
#include <gsl/gsl_errno.h>
#include <gsl/gsl_matrix.h>
#include <gsl/gsl_odeiv2.h>

typedef struct {
    double l, g;
} Params;

int func (double t, const double y[], double f[], void *params) {
    Params *p = (Params *) params;
    double l = p->l;
    double g = p->g;
    f[0] = y[1];
    f[1] = -(g/l)*y[0];
    return GSL_SUCCESS;
}

int jac (double t, const double y[], double *dfdy, double dfdt[],
         void *params) {
    Params *p = (Params *) params;
    double l = p->l;
    double g = p->g;
    gsl_matrix_view dfdy_mat = gsl_matrix_view_array (dfdy, 2, 2);
    gsl_matrix * m = &(dfdy_mat.matrix); 
    gsl_matrix_set (m, 0, 0, 0.0);
    gsl_matrix_set (m, 0, 1, 1.0);
    gsl_matrix_set (m, 1, 0, -(g/l));
    gsl_matrix_set (m, 1, 1, 0.0);
    dfdt[0] = 0.0;
    dfdt[1] = 0.0;
    return GSL_SUCCESS;
}

int main (void) {
    Params params;
    params.l = 1.0;
    params.g = 9.81;
    gsl_odeiv2_system sys = {func, jac, 2, &params};

    gsl_odeiv2_driver * d = gsl_odeiv2_driver_alloc_y_new (
            &sys, gsl_odeiv2_step_rk8pd, 1e-6, 1e-6, 0.0
    );
    int i;
    double t = 0.0, t1 = 100.0;
    double y[2] = { 0.1, 0.0 };

    for (i = 1; i <= 1000; i++) {
        double ti = i*t1/1000.0;
        int status = gsl_odeiv2_driver_apply (d, &t, ti, y);

        if (status != GSL_SUCCESS) {
            fprintf(stderr, "error, return value=%d\n", status);
            break;
        }

        printf ("%.5le %.5le %.5le\n", t, y[0], y[1]);
    }

    gsl_odeiv2_driver_free (d);
    return EXIT_SUCCESS;
}
