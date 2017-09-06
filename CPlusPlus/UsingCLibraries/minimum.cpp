#include <iostream>
#include <gsl/gsl_errno.h>
#include <gsl/gsl_min.h>

double func(const double x, void *params);

int main(int argc, char *argv[]) {
    double params[] {1.0, -1.0, 1.0};
    if (argc != 1 && argc != 4) {
        std::cerr << "### error: expecting x, x_min, x_max, or none"
                  << std::endl;
        std::exit(1);
    }
    double x {0.0};
    double x_min {-2.0};
    double x_max {2.0};
    if (argc == 4) {
        x = std::stod(argv[1]);
        x_min = std::stod(argv[2]);
        x_max = std::stod(argv[3]);
    }
    gsl_function F {
        .function = &func,
        .params = params
    };
    auto minimizer {gsl_min_fminimizer_alloc(gsl_min_fminimizer_brent)};
    int status {gsl_min_fminimizer_set(minimizer, &F, x, x_min, x_max)};
    if (status == GSL_EINVAL) {
        std::cerr << "### error: interval [" << x_min << ", " << x_max
                     << "] doesn't contain a minimum" << std::endl;
        std::exit(GSL_EINVAL);
    }
    std::cerr.precision(12);
    int iter_nr {0};
    int nr_iters {100};
    std::cerr << "# iter_nr x_min x x_max" << std::endl;
    std::cerr << iter_nr << " " << x_min << " " << x << " " << x_max
              << std::endl;
    do {
        iter_nr++;
        status = gsl_min_fminimizer_iterate(minimizer);
        x = gsl_min_fminimizer_x_minimum(minimizer);
        x_min = gsl_min_fminimizer_x_lower(minimizer);
        x_max = gsl_min_fminimizer_x_upper(minimizer);
        status = gsl_min_test_interval(x_min, x_max, 1e-6, 0.0);
        std::cerr << iter_nr << " " << x_min << " " << x << " "
                  << x_max << std::endl;
    } while (status == GSL_CONTINUE && iter_nr < nr_iters);
    if (status == GSL_SUCCESS) {
        std::cout << "converged at " << x
                  << ", minimum " << func(x, params) << std::endl;
    } else {
        std::cerr << "### warming: no convergence" << std::endl;
    }
    gsl_min_fminimizer_free(minimizer);
    return status;
    return 0;
}

double func(const double x, void *params) {
    auto params_arr = static_cast<double*>(params);
    double a {params_arr[0]};
    double b {params_arr[1]};
    double c {params_arr[2]};
    return (a*x + b)*x + c;
}
