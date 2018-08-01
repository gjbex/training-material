#include <stdio.h>

int sum(int a[], int n);

int main() {
    int a[] = {1, 2, 3, 4, 5};
    printf("sum = %d\n", sum(a, 5));
    for (int i = 0; i <= 5; i++)
        printf("%d\n", a[i]);
    return 0;
}

int sum(int a[], int n) {
    int sum = 0;
    for (int i = 0; i <= n; i++)
        sum += a[i];
    return sum;
}
