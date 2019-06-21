#include <stdio.h>

double logistic_map(double x0, double r, int steps) {
    int n;
    double x = x0;
    for (n = 0; n < steps; n++) {
        x = r*x*(1.0 - x);
    }
    return x;
}

