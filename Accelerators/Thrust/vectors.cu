#include <thrust/device_vector.h>
#include <thrust/sequence.h>
#include <functional>
#include <iostream>
#include <random>
#include <stdlib.h>
#include <sys/time.h>
#include <vector>

using namespace std;

struct saxpy_functor {
    private:
        const float a_;

    public:
        saxpy_functor(float a) : a_(a) {}

        __host__ __device__
        float operator()(const float& x, const float& y) const {
            return a_*x + y;
        }
};

float compute_time(struct timeval start_time, struct timeval end_time) {
    return (end_time.tv_sec - start_time.tv_sec) +
                1.0e-6*(end_time.tv_usec - start_time.tv_usec);
}

float thrust_compute(thrust::device_vector<float>& x,
                      thrust::device_vector<float>& y) {
    for (float a = 1.0e-5f; a < 1.0e-2f; a += 1.0e-5f)
        thrust::transform(x.begin(), x.end(), y.begin(), y.begin(),
                          saxpy_functor(a));
    float init {0.0f};
    thrust::plus<float> operation;
    return thrust::reduce(y.begin(), y.end(),
                          init, operation);
}

float host_compute(vector<float>& x, vector<float>& y) {
    for (float a = 1.0e-5f; a < 1.0e-2f; a += 1.0e-5f)
        for (int i = 0; i < x.size(); i++)
            y[i] += a*x[i];
    float result = 0.0f;
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
    vector<float> x_host(n);
    vector<float> y_host(n);
    for (int i = 0; i < x_host.size(); i++) {
        x_host[i] = i + 1.0;
        y_host[i] = i + 10.0;
    }
    gettimeofday(&start_time, NULL);
    thrust::device_vector<float> x = x_host;
    thrust::device_vector<float> y = y_host;
    gettimeofday(&end_time, NULL);
    cout << "data transfer time = " << compute_time(start_time, end_time)
         << endl;
    if (verbose) {
        cout << "x (GPU)" << endl;
        thrust::copy(x.begin(), x.end(),
                     ostream_iterator<float>(cout, "\n"));
        cout << "y (GPU)" << endl;
        thrust::copy(y.begin(), y.end(),
                     ostream_iterator<float>(cout, "\n"));
    }
    gettimeofday(&start_time, NULL);
    float thrust_result = thrust_compute(x, y);
    gettimeofday(&end_time, NULL);
    cout << "GPU compute time = " << compute_time(start_time, end_time)
         << endl;
    if (verbose) {
        cout << "GPU result" << endl;
        thrust::copy(y.begin(), y.end(),
                     ostream_iterator<float>(cout, "\n"));
    }
    cout << "GPU sum = " << thrust_result << endl;
    gettimeofday(&start_time, NULL);
    float host_result = host_compute(x_host, y_host);
    gettimeofday(&end_time, NULL);
    cout << "CPU compute time = " << compute_time(start_time, end_time)
         << endl;
    cout << "CPU sum = " << host_result << endl;
    return 0;
}
