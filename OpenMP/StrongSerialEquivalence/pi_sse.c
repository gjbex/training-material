#include <err.h>
#include <stdio.h>
#include <stdlib.h>
#ifdef _OPENMP
#include <omp.h>
#endif

int main(int argc, char *argv[]) {
    const int n = 1000;
    const double dx = 1.0/n;
    double pi = 0.0;
    FILE *fp;
    if (argc < 2)
        errx(EXIT_FAILURE, "no file name specified");
#ifdef _OPENMP
    omp_set_dynamic(0);
#endif
#pragma omp parallel default(none), shared(pi)
    {
        int i, num_threads = 1, thread_num;
        double pi_partial = 0.0;
#ifdef _OPENMP
        num_threads = omp_get_num_threads();
#endif
#pragma omp for schedule(static, 1 + (n - 1)/num_threads)
        for (i = 0; i < n; i++) {
            double x = i*dx;
            pi_partial += 4.0/(1.0 + x*x);
        }
#pragma omp for schedule(static, 1), ordered
        for (thread_num = 0; thread_num < num_threads; thread_num++)
#pragma omp ordered
            pi += pi_partial;
    }
    printf("%.15f\n", pi*dx);
    if ((fp = fopen(argv[1], "wb")) == NULL)
        err(EXIT_FAILURE, "can not open file");
    fwrite(&pi, sizeof(double), 1, fp);
    fclose(fp);
    return 0;
}
