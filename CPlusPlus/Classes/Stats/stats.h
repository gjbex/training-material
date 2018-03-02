#ifndef STATS_HDR
#define STATS_HDR

#include <iostream>

#include "simple_stats.h"

class Stats : public SimpleStats {
    private:
        double _sum2;
        using super = SimpleStats;
    public:
        Stats() : SimpleStats(), _sum2 {0.0} {};
        void add(double x) { super::add(x); _sum2 += x*x; };
        double sum2() const { return _sum2; };
        double stddev() const;
};

std::ostream& operator<<(std::ostream&, const Stats& stats);

#endif
