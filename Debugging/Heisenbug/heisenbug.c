#include <err.h>
#include <stdio.h>
#include <stdlib.h>

void init_data(int *data, int n);
int compute_sum(int *data, int n);
int expected_result(int n);

int main(int argc, char *argv[]) {
    const int max_p = 10;
    int n = 10;
    if (argc == 2)
        n = atoi(argv[1]);
    for (int i = 0; i < n; i++) {
        int p = 1 + rand() % max_p;
        int *data = (int *) malloc(p*sizeof(int));
        if (data == NULL)
            errx(EXIT_FAILURE, "can not allocate size %d array", p);
        init_data(data, p);
        int result = compute_sum(data, p);
        printf("data at %p, %d elements: %d vs. %d\n", data, p,
               result, expected_result(p));
        free(data);
    }
    return 0;
}

void init_data(int *data, int n) {
    for (int i = 0; i < n; i++)
        data[i] = i + 1;
}

int compute_sum(int *data, int n) {
    int sum = 0;
    for (int i = 0; i <= n; i++)
        sum += data[i];
    return sum;
}

int expected_result(int n) {
    return n*(n + 1)/2;
}
