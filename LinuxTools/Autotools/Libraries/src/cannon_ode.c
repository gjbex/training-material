#include <err.h>
#include <math.h>
#include <stdio.h>
#include <stdlib.h>
#include <gsl/gsl_errno.h>
#include <gsl/gsl_odeiv2.h>

#define X   y[0]
#define V_X y[1]
#define Y   y[2]
#define V_Y y[3]

const double g = 9.81;        /* m/s^2 */
const double v_0 = 700.0;     /* m/s */
const double B2_m = 4.0e-5;   /* 1/m */
const double y_d = 1.0e4;     /* m */

int func(double t, const double y[], double f[], void *params);

int main(int argc, char *argv[]) {
    gsl_odeiv2_system sys = {func, NULL, 4, NULL};
    gsl_odeiv2_driver *driver = gsl_odeiv2_driver_alloc_y_new(
            &sys, gsl_odeiv2_step_rkf45, 1.0e-6, 1.0e-6, 0.0
    );
    int i = 1;
    double t = 0.0;
    double alpha = argc > 1 ? strtod(argv[1], NULL) : 1.0;
    double y[4];
    X = Y = 0.0;
    V_X = v_0*cos(alpha);
    V_Y = v_0*sin(alpha);
    while (Y >= 0.0) {
        double t_i = i/50.0;
        int status = gsl_odeiv2_driver_apply(driver, &t, t_i, y);
        if (status != GSL_SUCCESS) {
            warnx("apply status = %d", status);
            break;
        }
        printf("%.12le %.12le %.12le %.12le %.12le\n", t, X, Y, V_X, V_Y);
        i++;
    }
    gsl_odeiv2_driver_free(driver);
    return EXIT_SUCCESS;
}

#define DX_DT f[0]
#define DVX_DT f[1]
#define DY_DT f[2]
#define DVY_DT f[3]

int func(double t, const double y[], double f[], void *params) {
    double v = sqrt(V_X*V_X + V_Y*V_Y);
    double corr = exp(-Y/y_d);
    DX_DT  = V_X;
    DVX_DT = -B2_m*corr*v*V_X;
    DY_DT  = V_Y;
    DVY_DT = -g - B2_m*corr*v*V_Y;
    return GSL_SUCCESS;
}
