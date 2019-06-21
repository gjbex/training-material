#ifndef STATISTICS_HDR
#define STATISTICS_HDR

#include <cmath>
#include <iostream>
#include <limits>
#include <string>

class Statistics {
    private:
        std::string _name;
        size_t _n;
        double _sum;
        double _sum2;
        double _min;
        double _max;
        size_t _nr_missing;
        void check() const;
        double sum2() const { check(); return _sum2; };
        double mean2() const { check(); return sum2()/n(); };
    public:
        Statistics() :
            _name {""}, _n {0}, _sum {0.0}, _sum2 {0.0},
            _min {std::numeric_limits<double>::max()},
            _max {-std::numeric_limits<double>::max()},
           _nr_missing {0} {};
        Statistics(const std::string& name) : Statistics() {
            _name = name;
        };
        const std::string& name() const { return _name; };
        size_t n() const { return _n; };
        void add(const double value);
        void add(const std::string& str);
        double sum() const { check(); return _sum; };
        double min() const { check(); return _min; };
        double max() const { check(); return _max; };
        double mean() const { check(); return sum()/n(); };
        double stddev() const {
            check();
            return sqrt((sum2() - sum()*sum()/n())/(n() - 1));
        };
        size_t nr_missing() const { return _nr_missing; };
        friend std::ostream& operator<<(std::ostream& out,
                                        const Statistics& stats);
};

#endif
