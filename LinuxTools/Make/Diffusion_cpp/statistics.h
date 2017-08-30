#ifndef STATISTICS_HDR
#define STATISTICS_HDR

#include <cmath>
#include <iostream>
#include <limits>

class Statistics {
    private:
        int _n;
        double _sum;
        double _sum2;
        double _min;
        double _max;
        void check() const;
    public:
        Statistics() :
            _n {0}, _sum {0.0}, _sum2 {0.0},
            _min {std::numeric_limits<double>::max()},
            _max {-std::numeric_limits<double>::max()} {};
        int n() const { return _n; };
        void add(const double value);
        double sum() const { check(); return _sum; };
        double sum2() const { check(); return _sum2; };
        double min() const { check(); return _min; };
        double max() const { check(); return _max; };
        double mean() const { check(); return sum()/n(); };
        double mean2() const { check(); return sum2()/n(); };
        double stddev() const {
            check();
            return sqrt((sum2() - sum()*sum()/n())/(n() - 1));
        };
        friend std::ostream& operator<<(std::ostream& out,
                                        const Statistics& stats);
};

#endif
