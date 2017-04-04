#include <armadillo>
#include <iostream>

using namespace arma;

int main(int argc, char *argv[]) {
    if (argc < 2) {
        std::cerr << "# error: no file specified" << std::endl;
        return 1;
    }
    mat A;
    A.load(argv[1], raw_ascii);
    if (A.n_rows != A.n_cols) {
        std::cerr << "# error: matrix should be square" << std::endl;
        return 2;
    }
    mat U, V;
    vec s;
    svd(U, s, V, A);
    U.print("U:");
    s.print("s:");
    V.print("V:");
    mat B = diagmat(s);
    mat Delta = abs((U*B)*V.t() - A);
    Delta.print("delta:");
    return 0;
}
