#include <stdexcept>

#include "table_stats.h"

TableStats::TableStats(const std::vector<std::string>& names) {
    names_ = std::make_unique<NameList>(names);
    stats_ = std::make_unique<StatsList>(names_->size());
}

void TableStats::add(const std::vector<double>& values) {
    if (values.size() != size())
        throw std::invalid_argument("expecting " + std::to_string(size()) +
                                 ", received " + std::to_string(values.size()));
    for (int i = 0; i < size(); ++i)
        (*stats_)[i].add(values[i]);
}
