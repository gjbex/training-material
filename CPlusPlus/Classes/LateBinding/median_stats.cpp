#include <algorithm>
#include <sstream>

#include "median_stats.h"

void MedianStats::add(const double value) {
    super::add(value);
    values_.push_back(value);
}

double MedianStats::median() {
    check_size(1);
    std::sort(values_.begin(), values_.end());
    size_t n {values_.size()};
    if (n % 2 == 0)
        return (values_[n/2 - 1] + values_[n/2])/2.0;
    else
        return values_[n/2];
}

std::string MedianStats::to_str() const {
    std::stringstream s;
    s << "\n\tvalues_:";
    for (const auto& value: values_)
        s << " " << value;
    return super::to_str() + s.str();
}

std::ostream& operator<<(std::ostream& out, const MedianStats& stats) {
    return out << stats.to_str();
}
