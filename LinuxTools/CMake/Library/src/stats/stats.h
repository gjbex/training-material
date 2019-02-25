#ifndef STATS_HDR
#define STATS_HDR

#include <cmath>
#include <limits>
#include <memory>
#include <stdexcept>
#include <vector>

class Stats {
    private:
        double sum_;
        double sum2_;
        double min_;
        double max_;
        std::unique_ptr<std::vector<double>> values_;
    public:
        Stats() : sum_ {0.0}, sum2_ {0.0},
                  min_ {std::numeric_limits<double>::max()},
                  max_ {std::numeric_limits<double>::min()},
                  values_ {std::make_unique<std::vector<double>>()} {}
        size_t nr_values() const { return values_->size(); }
        double mean() const;
        double stddev() const;
        double min() const;
        double max() const;
        void add(const double value);
        double median() const;
    private:
        void check_size(size_t n) const;
};

#endif
