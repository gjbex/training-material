#include <functional>
#include <iostream>
#include <stdlib.h>
#include <sys/time.h>
#include <vector>

using namespace std;

double compute_time(struct timeval start_time, struct timeval end_time) {
    return (end_time.tv_sec - start_time.tv_sec) +
                1.0e-6*(end_time.tv_usec - start_time.tv_usec);
}

double host_compute(vector<double>& x, vector<double>& y) {
    for (double a = 1.0e-5; a < 1.0e-2; a += 1.0e-5)
#pragma omp parallel for shared(x, y, a) default(none)
        for (int i = 0; i < x.size(); i++)
            y[i] += a*x[i];
    double result = 0.0;
#pragma omp parallel for reduction(+:result) shared(y) default(none)
    for (int i = 0; i < y.size(); i++)
        result += y[i];
    return result;
}

int main(int argc, char *argv[]) {
    const bool verbose = false;
    struct timeval start_time, end_time;
    int n = 5;
    if (argc > 1)
        n = atoi(argv[1]);
    vector<double> x_host(n);
    vector<double> y_host(n);
    for (int i = 0; i < x_host.size(); i++) {
        x_host[i] = i + 1.0;
        y_host[i] = i + 10.0;
    }
    gettimeofday(&start_time, NULL);
    double host_result = host_compute(x_host, y_host);
    gettimeofday(&end_time, NULL);
    cout << "CPU compute time = " << compute_time(start_time, end_time)
         << endl;
    cout << "CPU sum = " << host_result << endl;
    return 0;
}

