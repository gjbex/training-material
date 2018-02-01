#include <stdio.h>
#include <stdlib.h>

void do_mischief(int *n) {
    *n = 42;
}

int main() {
    const int n = 5;
    printf("originally, n = %d\n", n);
    do_mischief((int *) &n);
    printf("mischief accomplished, n = %d\n", n);
    return EXIT_SUCCESS;
}
