#include <stdio.h>
#include <stdlib.h>

int main(int argc, char *argv[]) {
    int n = 10;
    int i = 0;
    if (argc > 1)
        n = atoi(argv[1]);
    for (i = 2; i <= n; i++) {
        {
#ifdef HAS_BUG
            int i = 0;
#endif
            int j = 0;
            for (j = 2; j < i; j++)
                if (i % j == 0) {
                    printf("%i is not prime\n", i);
                    break;
                }
            if (j == i)
                printf("%d is prime\n", i);
        }
    }
    return EXIT_SUCCESS;
}
