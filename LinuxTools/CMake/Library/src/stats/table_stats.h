#include <memory>
#include <vector>

#include "stats.h"

using NameList = std::vector<std::string>;
using StatsList = std::vector<Stats>;

class TableStats {
    private:
        std::unique_ptr<NameList> names_;
        std::unique_ptr<StatsList> stats_;
    public:
        TableStats(const std::vector<std::string>& names);
        const NameList* names() const { return names_.get(); }
        size_t size() const { return names_->size(); }
        void add(const std::vector<double>& values);
        const StatsList* stats() const { return stats_.get(); }
};
