double log_map(double x, double r, int n) {
    int i;
    for (i = 0; i < n; i++) {
        x = r*x*(1.0 - x);
    }
    return x;
}

