#include <functional>
#include <iostream>
#include <random>
#include <sys/time.h>

extern "C" {
#include "cl_params.h"
}

using namespace std;

#ifndef WITHOUT_GPU_XT
void compute_gpu_xt(int n, int nr_iters);
#endif
#ifndef WITHOUT_CPU
void compute_cpu(int n, int nr_iters);
#endif

int main(int argc, char *argv[]) {
    Params params;
    initCL(&params);
    parseCL(&params, &argc, &argv);
    dumpCL(stdout, "# ", &params);
#ifndef WITHOUT_GPU_XT
    if (!params.skip_gpu_xt)
        compute_gpu_xt(params.N, params.nr_iters);
#endif
#ifndef WITHOUT_CPU
    if (!params.skip_cpu)
        compute_cpu(params.N, params.nr_iters);
#endif
    finalizeCL(&params);
    return 0;
}

double compute_time(struct timeval start_time, struct timeval end_time) {
    return (end_time.tv_sec - start_time.tv_sec) +
                1.0e-6*(end_time.tv_usec - start_time.tv_usec);
}

double compute_sum(float *ptr, int size) {
    float sum {0.0};
    for (int i = 0; i < size; i++)
        sum += ptr[i];
    return sum;
}

#ifndef WITHOUT_GPU_XT
#include <cublasXt.h>
void compute_gpu_xt(int n, int nr_iters) {
    struct timeval start_time, end_time;
    float *a {new float[n*n]};
    float *b {new float[n*n]};
    float *c {new float[n*n]};
    if (!(a && b && c)) {
        cerr << "#error: can't allocate memory" << endl;
        exit(1);
    }
    for (int i = 0; i < n*n; i++) {
        a[i] = i + 1.0;
        b[i] = i + 10.0;
        c[i] = 0.0;
    }
    float alpha {1.0};
    float beta {1.0};
    cublasXtHandle_t handle;
    cublasStatus_t status = cublasXtCreate(&handle);
    if (status != CUBLAS_STATUS_SUCCESS) {
        cerr << "# error: couldn't create handle: " << status << endl;
        exit(1);
    }
    const int nr_devices {2};
    int device_ids[] = {0, 1};
    cublasXtDeviceSelect(handle, nr_devices, device_ids);
    if (status != CUBLAS_STATUS_SUCCESS) {
        cerr << "# error: couldn't select devices: " << status << endl;
        exit(1);
    }
    int block_dim;
    cublasXtGetBlockDim(handle, &block_dim);
    cout << "block dimension = " << block_dim << endl;
    gettimeofday(&start_time, NULL);
    for (int i = 0; i < nr_iters; i++) {
        status = cublasXtSgemm(handle, CUBLAS_OP_N, CUBLAS_OP_N,
                               n, n, n, &alpha, a, n, b, n, &beta, c, n);
        if (status != CUBLAS_STATUS_SUCCESS) {
            cerr << "# error: cublasXtSgemm returned: " << status << endl;
            exit(1);
        }
    }
    gettimeofday(&end_time, NULL);
    cout << "GPU_XT computation time = "
         << compute_time(start_time, end_time) << endl
         << "GPU_XT sum = " << compute_sum(c, n*n) << endl;
    delete a;
    delete b;
    delete c;
    cublasXtDestroy(handle);
}
#endif

#ifndef WITHOUT_CPU
#include <armadillo>
using namespace arma;
void compute_cpu(int n, int nr_iters) {
    struct timeval start_time, end_time;
    auto A = Mat<float>(n, n);
    auto B = Mat<float>(n, n);
    auto C = Mat<float>(n, n, fill::zeros);
    int k = 0;
    for (int j = 0; j < n; j++) {
        for (int i = 0; i < n; i++) {
            A(i, j) = k + 1.0;
            B(i, j) = k + 10.0;
            k++;
        }
    }
    gettimeofday(&start_time, NULL);
    for (int i = 0; i < nr_iters; i++) {
        C += A*B;
    }
    gettimeofday(&end_time, NULL);
    cout << "CPU computation time = "
         << compute_time(start_time, end_time) << endl
         << "CPU sum = " << compute_sum(C.memptr(), C.n_rows*C.n_cols)
         << endl;
}
#endif
