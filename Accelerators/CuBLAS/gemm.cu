#include <functional>
#include <iostream>
#include <random>
#include <sys/time.h>
#include <cublasXt.h>

using namespace std;


double compute_time(struct timeval start_time, struct timeval end_time) {
    return (end_time.tv_sec - start_time.tv_sec) +
                1.0e-6*(end_time.tv_usec - start_time.tv_usec);
}

int main(int argc, char *argv[]) {
    const bool verbose = false;
    struct timeval start_time, end_time;
    int n = 5;
    if (argc > 1)
        n = atoi(argv[1]);
    float *a {new float[n*n]};
    float *b {new float[n*n]};
    float *c {new float[n*n]};
    if (!(a && b && c)) {
        cerr << "#error: can't allocate memory" << endl;
        return 1;
    }

    for (int i = 0; i < n*n; i++) {
        a[i] = i + 1.0;
        b[i] = i + 10.0;
        c[i] = 0.0;
    }
    float alpha {1.0};
    float beta {0.0};
    cublasXtHandle_t handle;
    cublasStatus_t status = cublasXtCreate(&handle);
    const int nr_devices {2};
    int device_ids[] = {1, 1};
    cublasXtDeviceSelect(handle, nr_devices, device_ids);
    if (status != CUBLAS_STATUS_SUCCESS) {
        cerr << "# error: couldn't create handle: " << status << endl;
        return 1;
    }
    gettimeofday(&start_time, NULL);
    status = cublasXtSgemm(handle, CUBLAS_OP_N, CUBLAS_OP_N,
                           n, n, n, &alpha, a, n, b, n, &beta, c, n);
    gettimeofday(&end_time, NULL);
    cout << "computation time = " << compute_time(start_time, end_time)
         << endl;
    float sum {0.0};
    for (int i = 0; i < n*n; i++)
        sum += c[i];
    cout << "sum = " << sum << endl;
    delete a;
    delete b;
    delete c;
    cublasXtDestroy(handle);
    return 0;
}
