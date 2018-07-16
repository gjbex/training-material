#include <omp.h>
#include <stdio.h>

int main() {
#pragma omp parallel
    {
        int thread_num = omp_get_thread_num();
        printf("thread %d\n", thread_num);
        if (thread_num == 0) {
            int num_threads = omp_get_num_threads();
            printf("%d total threads\n", num_threads);
        }
    }
    return 0;
}
