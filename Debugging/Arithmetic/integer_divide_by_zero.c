#include <stdio.h>

int main() {
    int a[] = {-2, 1, 0, 1, 2};
    int b = 5;
    for (int i = 0; i < 5; i++)
        printf("%d/%d = %d\n", b, a[i], b/a[i]);
    return 0;
}
