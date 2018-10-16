#include <stdio.h>

int main(int argc, char *argv[]) {
    int a = atoi(argv[1]);
    int b = atoi(argv[2]);
    if (a < 3 & 5 < b)
        printf("a = %d\n", a);
    else
        printf("b = %d\n", b);
    return 0;
}
