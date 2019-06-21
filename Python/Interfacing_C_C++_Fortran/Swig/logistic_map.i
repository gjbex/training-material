%module log_map
%{
#define SWIG_FILE_WITH_INIT
extern double logistic_map(double x, double r, int steps);
%}

extern double logistic_map(double x, double r, int steps);

