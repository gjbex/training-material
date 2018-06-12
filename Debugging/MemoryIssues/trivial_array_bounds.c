#include <stdio.h>

int main() {
    const int n = 10;
    int data[n];
    for (int i = 0; i < n; i++)
        data[i] = i;
    for (int i = 0; i < n; i++)
        data[i] = data[i] + data[i-1];
    for (int i = 0; i < n; i++)
        printf("%d: %d\n", i, data[i]);
    return 0;
}
