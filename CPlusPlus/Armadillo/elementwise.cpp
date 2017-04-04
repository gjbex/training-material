#include <armadillo>
#include <iostream>

using namespace arma;

int main() {
    const size_t nr_rows {3};
    const size_t nr_cols {2};
    mat A(nr_rows, nr_cols);
    for (size_t j = 0; j < A.n_cols; j++)
        for (size_t i = 0; i < A.n_rows; i++)
            A(i, j) = sqrt(i + j);
    A.print("A:");
    A.transform([] (double x) { return x*x; });
    A.print("A.^2:");
    mat B = A.submat(span(0, 1), span(0, 1));
    B.print("B:");
    rowvec x = A.row(2);
    x.print("x:");
    x(0) = 19.0;
    x(1) = -13.0;
    A.print("A:");
    return 0;
}
