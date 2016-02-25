#include <stdio.h>
#include <stdlib.h>
#include <omp.h>

int main(int argc, char *argv[]) {
    int thread_num = 0, num_threads = 1;
#ifdef _OPENMP
    thread_num = omp_get_thread_num();
    num_threads = omp_get_num_threads();
    if (thread_num == 0)
        printf("yes, we've got OpenMP!\n");
#endif
    printf("hello from thread %d out of %d\n", thread_num, num_threads);
    return EXIT_SUCCESS;
}
