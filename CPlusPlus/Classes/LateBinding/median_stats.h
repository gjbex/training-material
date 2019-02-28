#ifndef MEDIAN_STATS_HDR
#define MEDIAN_STATS_HDR

#include <iostream>
#include <vector>

#include "stats.h"

class MedianStats : public Stats {
    private:
        std::vector<double> values_;
        using super = Stats;
    public:
        MedianStats() : Stats() {}
        double median();
        void add(const double value) override;
        std::string to_str() const override;
        friend std::ostream& operator<<(std::ostream& out,
                                        const MedianStats& stats);
};

#endif
