#include <R.h>

/* sayHello part not shown */

void mySum(double *a, int* n, double *s) {
        int i;
            *s = 0.0;
                for (i = 0; i < *n; i++)
                            *s += a[i];
}
