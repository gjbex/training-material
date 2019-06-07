#include <Eigen/Dense>
#include <iostream>
#include "string_aligner.h"

int main(int argc, char* argv[]) {
    if (argc != 3) {
        std::cerr << "Error: two strings expected as arguments" << std::endl;
        std::exit(1);
    }
    std::string str1(argv[1]);
    std::string str2(argv[2]);
    Matrix_t scoring_matrix(4, 4);
    const std::string alphabet("ACGT");
    scoring_matrix <<  2, -1,  1, -1,
                      -1,  2, -1,  1,
                       1, -1,  2, -1,
                      -1,  1, -1,  2;
    const int gap_socre {-2};
    StringAligner aligner(alphabet, scoring_matrix, gap_socre);
    auto [aligned1, aligned2] = aligner.align(str1, str2);
    std::cout << aligned1 << "\n"
              << aligned2 << std::endl;
    return 0;
}
