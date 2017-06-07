#include <armadillo>
#include <functional>
#include <iostream>
#include <random>
#include <sys/time.h>
#include <cublasXt.h>

using namespace std;
using namespace arma;

double compute_time(struct timeval start_time, struct timeval end_time) {
    return (end_time.tv_sec - start_time.tv_sec) +
                1.0e-6*(end_time.tv_usec - start_time.tv_usec);
}

int main(int argc, char *argv[]) {
    float sum {0.0};
    struct timeval start_time, end_time;
    int n = 500;
    if (argc > 1)
        n = atoi(argv[1]);
    int nr_iters = 10;
    if (argc > 2)
        nr_iters = atoi(argv[2]);
    cout << n << "x" << n << " matrices, " << nr_iters << " iterations"
         << endl;
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
    float beta {1.0};
    cout << "host matrices allocated and initialized" << endl;
    cublasXtHandle_t handle;
    cublasStatus_t status = cublasXtCreate(&handle);
    const int nr_devices {2};
    int device_ids[] = {0, 1};
    cublasXtDeviceSelect(handle, nr_devices, device_ids);
    if (status != CUBLAS_STATUS_SUCCESS) {
        cerr << "# error: couldn't create handle: " << status << endl;
        return 1;
    }
    gettimeofday(&start_time, NULL);
    for (int i = 0; i < nr_iters; i++) {
        status = cublasXtSgemm(handle, CUBLAS_OP_N, CUBLAS_OP_N,
                               n, n, n, &alpha, a, n, b, n, &beta, c, n);
    }
    gettimeofday(&end_time, NULL);
    cout << "GPU computation time = " << compute_time(start_time, end_time)
         << endl;
    sum = 0.0;
    for (int i = 0; i < n*n; i++)
        sum += c[i];
    cout << "GPU sum = " << sum << endl;
    delete a;
    delete b;
    delete c;
    cublasXtDestroy(handle);

    auto A = Mat<float>(n, n);
    auto B = Mat<float>(n, n);
    auto C = Mat<float>(n, n);
    int k = 0;
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < n; j++) {
            A(i, j) = k + 1.0;
            B(i, j) = k + 10.0;
            C(i, j) = 0.0;
            k++;
        }
    }
    cout << "CPU matrices allocated and initialized" << endl;
    gettimeofday(&start_time, NULL);
    for (int i = 0; i < nr_iters; i++) {
        C += A*B;
    }
    gettimeofday(&end_time, NULL);
    cout << "CPU computation time = " << compute_time(start_time, end_time)
         << endl;
    sum = 0.0;
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < n; j++) {
            sum += C(i, j);
        }
    }
    cout << "CPU sum = " << sum << endl;
    return 0;
}
