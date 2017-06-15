#include <algorithm>
#include <cmath>
#include <iomanip>
#include <iostream>
#include <vector>

using namespace std;

struct Stats {
    double mean, stddev, median;
    int n;
};

vector<double> read_data(istream& in);
Stats compute_stats(vector<double> data);

int main() {
    auto data {read_data(cin)};
    auto stats {compute_stats(data)};
    cout << "mean = " << stats.mean << endl;
    cout << "std.dev. = " << stats.stddev << endl;
    cout << "median = " << stats.median << endl;
    cout << "n = " << stats.n << endl;
    return 0;
}

vector<double> read_data(istream& in) {
    vector<double> data;
    double item;
    while (in >> item)
        data.push_back(item);
    return data;
}

Stats compute_stats(vector<double> data) {
    int n = data.size();
    double sum {0.0};
    double sum2 {0.0};
    for (double item: data) {
        sum += item;
        sum2 += item*item;
    }
    Stats stats;
    stats.mean = sum/n;
    stats.stddev = sqrt(sum2/n - stats.mean*stats.mean);
    sort(data.begin(), data.end());
    int middle {n/2};
    stats.median = n % 2 == 1 ? data.at(middle) :
        (data.at(middle - 1) + data.at(middle))/2.0;
    stats.n = n;
    return stats;
}
