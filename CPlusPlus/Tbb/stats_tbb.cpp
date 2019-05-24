#include <cmath>
#include <iostream>
#include <limits>
#include <random>
#include <tbb/tbb.h>
#include <valarray>

using Vector = std::valarray<double>;

class Stats {
    private:
        Vector* const data_;
        const std::size_t n_;
        double sum_;
        double sum2_;
        double min_;
        double max_;
    public:
        Stats(Vector* data) : data_ {data}, n_ {data->size()}, sum_ {0.0}, sum2_ {0.0},
            min_ {std::numeric_limits<double>::max()},
            max_ {std::numeric_limits<double>::min()} {}
        Stats(Stats& stats, tbb::split) : Stats(stats.data_) {}
        void operator()(const tbb::blocked_range<std::size_t>& r);
        void join(const Stats& stats);
        std::size_t n() const { return n_; }
        double mean() const { return sum_/n_; }
        double stddev() const;
        double min() const { return min_; }
        double max() const { return max_; }
};

void Stats::operator()(const tbb::blocked_range<std::size_t>& r) {
    for (auto i = r.begin(); i != r.end(); ++i) {
        double val = (*data_)[i];
        sum_ += val;
        sum2_ += val*val;
        min_ = std::min(val, min_);
        max_ = std::max(val, max_);
    }
}

void Stats::join(const Stats& stats) {
    sum_ += stats.sum_;
    sum2_ += stats.sum2_;
    min_ = std::min(stats.min_, min_);
    max_ = std::max(stats.max_, max_);
}

double Stats::stddev() const {
    using std::sqrt;
    return sqrt((sum2_ - sum_*sum_/n_)/(n_ - 1));
}

using Seed_t = std::mt19937_64::result_type;

void init_data(Vector& data, const Seed_t seed) {
    std::mt19937_64 engine(seed);
    std::normal_distribution<double> distr(0.0, 1.0);
    for (auto& val: data)
        val = distr(engine);
}

int main(int argc, char* argv[]) {
    std::size_t n {100};
    std::size_t grain_size {5000};
    Seed_t seed {1234};
    if (argc > 1)
        n = std::stoul(argv[1]);
    if (argc > 2)
        grain_size = std::stoul(argv[2]);
    if (argc > 3)
        seed = std::stoul(argv[3]);
    Vector data(n);
    init_data(data, seed);
    Stats stats(&data);
    tbb::parallel_reduce(tbb::blocked_range<std::size_t>(0, data.size(), grain_size), stats);
    std::cout << "mean = " << stats.mean() << "\n"
              << "stddev = " << stats.stddev() << "\n"
              << "min = " << stats.min() << "\n"
              << "max = " << stats.max() << "\n"
              << "n = " << stats.n() << std::endl;;
    return 0;
}
