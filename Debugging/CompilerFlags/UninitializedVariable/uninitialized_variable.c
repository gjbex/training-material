#include <stdio.h>
#include <stdlib.h>

double compute_sum(int n) {
    double sum;
    int i;
    srand(123);
    for (i = 0; i < n; i++)
        sum += ((double) rand())/RAND_MAX;
    return sum/n;

}

int main() {
    const int n = 5;
    double sum;
    int i;
    for (i = 0; i < n; i++) {
        sum = compute_sum(n);
        printf("sum = %lf\n", sum);
    }
    return EXIT_SUCCESS;
}
