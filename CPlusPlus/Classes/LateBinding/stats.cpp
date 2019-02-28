#include <algorithm>
#include <cmath>
#include <sstream>
#include <stdexcept>

#include "stats.h"

void Stats::add(const double value) {
    ++nr_values_;
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

std::string Stats::to_str() const {
    std::stringstream s;
    s << "sum_: " << sum_ << ", sum2_: " << sum2_
      << ", min_: " << min_ << ", max_: " << max_
      << ", nr_values_: " << nr_values_;
    return s.str();
}

std::ostream& operator<<(std::ostream& out, const Stats& stats) {
    return out << stats.to_str();
}

void Stats::check_size(size_t n) const {
    if (nr_values() < n)
        throw std::out_of_range("insufficient data, at least " +
                                std::to_string(n) + " values required");
}
