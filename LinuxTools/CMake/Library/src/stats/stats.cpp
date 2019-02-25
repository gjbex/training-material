#include <algorithm>
#include "stats.h"

void Stats::add(const double value) {
    values_->push_back(value);
    sum_ += value;
    sum2_ += value*value;
    if (value < min_)
        min_ = value;
    if (value > max_)
        max_ = value;
}

double Stats::mean() const {
    check_size(1);
    return sum_/nr_values();
}

double Stats::stddev() const {
    check_size(2);
    return sqrt((sum2_ - sum_*sum_/nr_values())/(nr_values() - 1));
} 

double Stats::min() const {
    check_size(1);
    return min_;
}

double Stats::max() const {
    check_size(1);
    return max_;
}

double Stats::median() const {
    check_size(1);
    std::sort(values_->begin(), values_->end());
    size_t n {values_->size()};
    if (n % 2 == 0)
        return ((*values_)[n/2 - 1] + (*values_)[n/2])/2.0;
    else
        return (*values_)[n/2];
}

void Stats::check_size(size_t n) const {
    if (nr_values() < n)
        throw std::out_of_range("insufficient data, at least " +
                                std::to_string(n) + " values required");
}
