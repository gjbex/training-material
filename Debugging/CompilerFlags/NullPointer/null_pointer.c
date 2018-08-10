#include <stdio.h>
#include <stdlib.h>

int main() {
    long size = 10000000000000;
    int *data = (int *) malloc(size*sizeof(int));
    for (long i = 0; i < size; i++)
        data[i] = i;
    long sum = 0;
    for (long i = 0; i < size; i++)
        sum += data[i];
    printf("sum = %ld\n", sum);
    return 0;
}
