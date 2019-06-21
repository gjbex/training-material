#include <math.h>

#include "stats.h"

Stats stats(double *data, int n) {
    Stats s;
    double sum = 0.0, sum2 = 0.0;
    int i;
    for (i = 0; i < n; i++) {
        sum += data[i];
        sum2 += data[i]*data[i];
    }
    s.mean = sum/n;
    s.stddev = sqrt(sum2/n - s.mean*s.mean);
    s.n = n;
    return s;
}

