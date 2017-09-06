#include <cmath>
#include <iostream>
#include <tuple>
#include <gsl/gsl_errno.h>
#include <gsl/gsl_math.h>
#include <gsl/gsl_min.h>
#include <gsl/gsl_odeiv2.h>

const double g {9.81};        /* m/s^2 */
const double v_0 {700.0};     /* m/s */
const double B2_m {4.0e-5};   /* 1/m */
const double y_d {1.0e4};     /* m */
const double PI {3.14159265359};

int func(double t __attribute__((unused)), const double y[], double f[],
         void *params __attribute__((unused)));
double shot_range(const double alpha, void *params);
double deg2rad(const double angle);
double rad2deg(const double angle);

int main(int argc, char *argv[]) {
    int iter_nr {0};
    int nr_iters {100};
    double min_alpha {deg2rad(3.0)};
    double max_alpha {deg2rad(87.0)};
    double alpha {deg2rad(30.0)};
    double extrema[2];
    if (argc > 1)
        alpha = deg2rad(std::stod(argv[1]));
    gsl_function F {
        .function = &shot_range,
        .params = extrema
    };
    auto minimizer = gsl_min_fminimizer_alloc(gsl_min_fminimizer_brent);
    gsl_min_fminimizer_set(minimizer, &F, alpha, min_alpha, max_alpha);
    std::cerr.precision(12);
    std::cout.precision(12);
    std::cerr << "# iter_nr min_alpha max_alpha alpha range" << std::endl;
    std::cerr << iter_nr << " " << rad2deg(min_alpha) << " "
              << rad2deg(max_alpha) << " " << rad2deg(alpha) << " "
              << -shot_range(alpha, &extrema) << std::endl;
    int status;
    do {
        iter_nr++;
        status = gsl_min_fminimizer_iterate(minimizer);
        alpha = gsl_min_fminimizer_x_minimum(minimizer);
        min_alpha = gsl_min_fminimizer_x_lower(minimizer);
        max_alpha = gsl_min_fminimizer_x_upper(minimizer);
        status = gsl_min_test_interval(min_alpha, max_alpha, 1e-6, 0.0);
        std::cerr << iter_nr << " " << rad2deg(min_alpha) << " "
                  << rad2deg(max_alpha) << " "
                  << rad2deg(alpha) << " " << extrema[0] << std::endl;
    } while (status == GSL_CONTINUE && iter_nr < nr_iters);
    if (status == GSL_SUCCESS) {
        std::cout << "converged at " << rad2deg(alpha)
                  << ", range " << extrema[0]
                  << ", max. altitude " << extrema[1] << std::endl;
    } else {
        std::cerr << "### warming: no convergence" << std::endl;
    }
    gsl_min_fminimizer_free(minimizer);
    return status;
}

#define X   y[0]
#define V_X y[1]
#define Y   y[2]
#define V_Y y[3]

#define DX_DT  f[0]
#define DVX_DT f[1]
#define DY_DT  f[2]
#define DVY_DT f[3]

int func(double t __attribute__((unused)), const double y[], double f[],
         void *params __attribute__((unused))) {
    double v {sqrt(V_X*V_X + V_Y*V_Y)};
    double corr {exp(-Y/y_d)};
    DX_DT  = V_X;
    DVX_DT = -B2_m*corr*v*V_X;
    DY_DT  = V_Y;
    DVY_DT = -g - B2_m*corr*v*V_Y;
    return GSL_SUCCESS;
}

double shot_range(const double alpha, void *params) {
    gsl_odeiv2_system sys = {func, NULL, 4, NULL};
    auto driver = gsl_odeiv2_driver_alloc_y_new(
            &sys, gsl_odeiv2_step_rkf45, 1.0e-6, 1.0e-6, 0.0
    );
    int i {1};
    double t {0.0};
    double y[4];
    double h_max {0.0};
    X = Y = 0.0;
    V_X = v_0*cos(alpha);
    V_Y = v_0*sin(alpha);
    while (y[2] >= 0.0) {
        double t_i {i/50.0};
        int status {gsl_odeiv2_driver_apply(driver, &t, t_i, y)};
        if (status != GSL_SUCCESS) {
            std::cerr << "### warning: apply status = " << status
                      << std::endl;
            break;
        }
        if (Y > h_max)
            h_max = Y;
        i++;
    }
    gsl_odeiv2_driver_free(driver);
    auto params_arr = static_cast<double*>(params);
    params_arr[0] = X;
    params_arr[1] = h_max;
    return -X;
}

double deg2rad(const double angle) {
    return 2*PI*angle/360.0;
}

double rad2deg(const double angle) {
    return 360.0*angle/(2*PI);
}
