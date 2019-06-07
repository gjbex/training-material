#ifndef STRING_ALIGNER_HDR
#define STRING_ALIGNER_HDR

/*
 * Based on: http://www.biorecipes.com/DynProgBasic/code.html
 */

#include <Eigen/Dense>
#include <map>
#include <memory>
#include <vector>

using Alignment_t = std::pair<std::string,std::string>;
using Matrix_t = Eigen::MatrixXi;

class StringAligner {
    private:
        using Matrix_ptr_t = std::unique_ptr<Matrix_t>;
        Matrix_ptr_t scoring_matrix_;
        int gap_score_;
        std::string str1_;
        std::vector<int> rep1_;
        std::string str2_;
        std::vector<int> rep2_;
        std::map<char,int> dict_;
        void translate(const std::string& str1, const std::string& str2);
        int score(const int i, const int j) const {
            return (*scoring_matrix_)(i, j);
        }
    public:
        StringAligner(const std::string& alphabet, const Matrix_t& matrix,
                      const int gap_score);
        Alignment_t align(const std::string& s1, const std::string& s2);
};

#endif
