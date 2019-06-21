#ifndef STATS_HDR
#define STATS_HDR

typedef struct {
    double mean, stddev;
    int n;
} Stats;

Stats stats(double *data, int n);

#endif

