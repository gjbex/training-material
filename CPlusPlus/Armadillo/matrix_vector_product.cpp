#include <armadillo>
#include <iostream>

using namespace arma;

int main() {
    mat A {{1.0, 2.0}, {3.0, 4.0}};
    A.print("A:");
    colvec v {5.0, 6.0};
    v.print("v:");
    colvec w = A*v;
    w.print("A*v:");
    return 0;
}
