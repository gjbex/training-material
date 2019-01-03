#include <fstream>
#include <istream>
#include <iostream>
#include <xtensor/xarray.hpp>
#include <xtensor/xcsv.hpp>
#include <xtensor/xio.hpp>
#include <xtensor/xview.hpp>
#include <xtensor-blas/xlinalg.hpp>

int main(int argc, char *argv[]) {
    if (argc != 2) {
        std::cerr << "### error: no file specified" << std::endl;
        return 1;
    }
    std::ifstream in_file;
    in_file.open(argv[1]);
    if (!in_file) {
        std::cerr << "### error: can't open '" << argv[1] << "'"
                  << std::endl;
        return 2;
    }
    auto A = xt::load_csv<double>(in_file);
    std::cout << "A:" << std::endl << A << std::endl;
    auto [U, s, V] = xt::linalg::svd(A);
    std::cout << "U:" << std::endl << U << std::endl;
    std::cout << "s:" << std::endl << s << std::endl;
    std::cout << "V:" << std::endl << V << std::endl;
    auto Delta = fabs(xt::linalg::dot(U*s, V) - A);
    std::cout << "b:" << std::endl << Delta << std::endl;
    return 0;
}
