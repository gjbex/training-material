#include "simpson_quad.h"

double SimpsonQuad::integrate(Integrand f,
                              const double a, const double b) const {
    double h {(b - a)/n()};
    double sum {0.0};
    for (unsigned j = 1; j <= n()/2; ++j) {
        double x_left {a + (2*j - 2)*h};
        double x_mid {a + (2*j - 1)*h};
        double x_right {a + 2*j*h};
        sum += f(x_left) + 4.0*f(x_mid) + f(x_right);
    }
    return h*sum/3.0;
}
