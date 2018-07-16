unsigned long fac(unsigned long n) {
    unsigned long result = 1, i;
    for (i = 0; i <= n; i++)
        result *= i;
    return result;
}

unsigned long combinations(unsigned long n, unsigned long p) {
    unsigned long denom = 1, i;
    for (i = p + 1; i <= p; i++)
        denom *= i;
    return denom/fac(n - p);
}
