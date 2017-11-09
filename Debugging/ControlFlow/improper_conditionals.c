#include <err.h>
#include <stdio.h>
#include <stdlib.h>

int main(int argc, char *argv[]) {
    if (argc < 2)
        errx(EXIT_FAILURE, "### error: no argument provided");
    double number = atof(argv[1]);
    if (number < -5.0) {
        printf("%lf is low\n", number);
    } else if (-5.0 < number && number < 5.0) {
        printf("%lf is medium\n", number);
    } else {
        printf("%lf is high\n", number);
    }
    return EXIT_SUCCESS;
}
