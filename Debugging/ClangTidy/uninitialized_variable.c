#include <stdio.h>
#include <stdlib.h>

double compute_avg(int n, int seed) {
    double sum;
    int i;
    srand(seed);
    for (i = 0; i < n; i++)
        sum += ((double) rand())/RAND_MAX;
    return sum/n;

}

int main() {
    const int seed = 123;
    const int n = 5;
    int i;
    for (i = 0; i < n; i++) {
        double avg = compute_avg(n, seed);
        printf("avg = %lf\n", avg);
    }
    return EXIT_SUCCESS;
}
