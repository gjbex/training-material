#include <cmath>
#include <iostream>
#include <vector>
#include <xtensor/xarray.hpp>
#include <xtensor/xio.hpp>
#include <xtensor/xvectorize.hpp>
#include <xtensor/xview.hpp>

int main(int argc, char *argv[]) {
    size_t nr_rows {3};
    size_t nr_cols {4};
    if (argc == 3) {
        nr_rows = std::stoi(argv[1]);
        nr_cols = std::stoi(argv[2]);
    } else if (argc != 1) {
        std::cerr << "# error: expecting array dimensions or no arguments"
                  << std::endl;
        return 1;
    }
    std::vector<size_t> shape {nr_rows, nr_cols};
    xt::xarray<double, xt::layout_type::row_major> A(shape);
    for (size_t i = 0; i < A.shape()[0]; ++i)
        for (size_t j = 0; j < A.shape()[1]; ++j)
            A(i, j) = sqrt(i + j);
    std::cout << "A:" << std::endl << A << std::endl;
    auto A_sqr = A*A;
    std::cout << "A*A:" << std::endl << A_sqr << std::endl;
    auto sqr_vec = xt::vectorize([] (double x) { return x*x; });
    std::cout << "sqr_vec(A):" << std::endl << sqr_vec(A) << std::endl;
    if (A.shape()[0] >= 2 && A.shape()[1] >= 2) {
        auto B = xt::view(A, xt::range(0, 2), xt::range(0, 2));
        std::cout << "B:" << std::endl << B << std::endl;
    }
    if (A.shape()[0] > 2) {
        auto x = xt::flatten(xt::view(A, xt::range(2, 3), xt::all()));
        std::cout << "A(2, :):" << std::endl << x << std::endl;;
        if (x.shape()[0] > 1) {
            x(0) = 19.0;
            x(1) = -13.0;
            std::cout << "A:" << std::endl << A << std::endl;
        }
    }
    return 0;
}
