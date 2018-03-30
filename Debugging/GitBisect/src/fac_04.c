unsigned long fac(unsigned long n) {
    unsigned long result = 1, i;
    for (i = 0; i <= n; i++)
        result *= i;
    return result;
}
