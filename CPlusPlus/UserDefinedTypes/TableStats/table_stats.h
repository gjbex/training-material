#include <vector>

#include "stats.h"

using NameList = std::vector<std::string>;
using StatsList = std::vector<Stats>;
using ValueList = std::vector<double>;

class TableStats {
    private:
        NameList names_;
        StatsList stats_;
    public:
        TableStats(const NameList& names);
        const NameList& names() const { return names_; }
        size_t size() const { return names_.size(); }
        void add(const ValueList& values);
        const StatsList& stats() const { return stats_; }
};
