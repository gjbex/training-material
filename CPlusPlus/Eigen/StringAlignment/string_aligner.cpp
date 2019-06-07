#include "string_aligner.h"

StringAligner::StringAligner(const std::string& alphabet,
                             const Matrix_t& matrix,
                             const int gap_score) {
    scoring_matrix_ = std::make_unique<Matrix_t>(matrix);
    int idx {0};
    for (const auto& c: alphabet)
        dict_.insert(std::make_pair(c, idx++));
    gap_score_ = gap_score;
}

void StringAligner::translate(const std::string& str1, const std::string& str2) {
    // ensure to clear the representations since the align method can be
    // called multiple times
    rep1_.clear();
    // index arithmetic is easier when the string representation length is
    // equal to the corresponding distance matrix dimension
    rep1_.push_back(-1);
    for (const auto& c: str1)
        rep1_.push_back(dict_[c]);
    rep2_.clear();
    rep2_.push_back(-1);
    for (const auto& c: str2)
        rep2_.push_back(dict_[c]);
}

int max(const int a, const int b, const int c) {
    return std::max(a, std::max(b, c));
}

Alignment_t StringAligner::align(const std::string& s1, const std::string& s2) {
    str1_ = s1;
    str2_ = s2;
    translate(s1, s2);
    Matrix_t dists(s1.size() + 1, s2.size() + 1);
    dists(0, 0) = 0;
    for (long i = 1; i < dists.rows(); ++i)
        dists(i, 0) = dists(i - 1, 0) + gap_score_;
    for (long j = 1; j < dists.cols(); ++j)
        dists(0, j) = dists(0, j - 1) + gap_score_;
    for (long i = 1; i < dists.rows(); ++i) {
       for (long j = 1; j < dists.cols(); ++j) {
            int match = dists(i - 1, j - 1) + score(rep1_[i], rep2_[j]);
            int gap1 = dists(i, j - 1) + gap_score_;
            int gap2 = dists(i - 1, j) + gap_score_;
            dists(i, j) = max(match, gap1, gap2);
        }
    }
    std::string a1("");
    std::string a2("");
    long i {dists.rows() - 1};
    long j {dists.cols() - 1};
    while (i > 0 && j > 0) {
        if (dists(i, j) == dists(i - 1, j - 1) + score(rep1_[i], rep2_[j])) {
                a1 = str1_[-1 + i--] + a1;
                a2 = str2_[-1 + j--] + a2;
        } else if (dists(i, j) == dists(i - 1, j) + gap_score_) {
                a1 = str1_[-1 + i--] + a1;
                a2 = "_" + a2;
        } else if (dists(i, j) == dists(i, j - 1) + gap_score_) {
                a1 = "_" + a1;
                a2 = str2_[-1 + j--] + a2;
        }
    }
    if (i > 0)
        while (i > 0) {
            a1 = str1_[-1 + i--] + a1;
            a2 = "_" + a2;
        }
    else if (j > 0)
        while (j > 0) {
            a1 = "_" + a1;
            a2 = str2_[ -1 + j--] + a2;
        }
    return Alignment_t(a1, a2);
}

