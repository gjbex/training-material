#include <algorithm>
#include <stdexcept>

#include "table_stats.h"

TableStats::TableStats(const NameList& names) : names_ {names} {
    stats_.resize(names.size());
}

void TableStats::add(const ValueList& values) {
    if (values.size() != size())
        throw std::invalid_argument("expecting " + std::to_string(size()) +
                                 ", received " + std::to_string(values.size()));
    for (size_t i = 0; i < size(); ++i)
        stats_[i].add(values[i]);
}
