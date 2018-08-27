#include <err.h>
#include <stdio.h>
#include <stdlib.h>

int main(int argc, char *argv[]) {
    long n;
    double a;
    n = 5;
    a = 3.14;
    if (argc > 1)
        n = atol(argv[1]);
    if (argc > 2)
        a = atof(argv[2]);
    printf("atol: n = %ld, atof: a = %lf\n", n, a);
    n = 5;
    a = 3.14;
    if (argc > 1) {
        char *end_ptr = argv[1];
        n = strtol(argv[1], &end_ptr, 10);
        if (*end_ptr != '\0' || end_ptr == argv[1])
            warnx("'%s' could not be (completely) converted to long",
                  argv[1]);
    }
    if (argc > 2) {
        char *end_ptr = argv[2];
        a = strtod(argv[2], &end_ptr);
        if (*end_ptr != '\0' || end_ptr == argv[2])
            warnx("'%s' could not be (completely) converted to double",
                  argv[2]);
           printf("%c\n", *end_ptr);
    }
    printf("strtol: n = %ld, strtod: a = %lf\n", n, a);
    return 0;
}
