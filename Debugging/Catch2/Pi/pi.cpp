#include "pi.h"

double pi(int n) {
    double sum {0.0};
    double x {0.0};
    double dx {1.0/n};
    for (int i = 0; i < n; ++i) {
        x += dx;
        sum += 1.0/(1.0 + x*x);
    }
    return 4.0*dx*sum;
}
