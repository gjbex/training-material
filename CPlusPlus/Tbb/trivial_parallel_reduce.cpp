#include <iostream>
#include <numeric>
#include <tbb/tbb.h>
#include <valarray>

int main(int argc, char *argv[]) {
    std::size_t grain_size {1000};
    std::size_t array_size {100};
    if (argc > 1)
        array_size = std::stoi(argv[1]);
    std::valarray<int> data(array_size);
    std::iota(std::begin(data), std::end(data), 0);
    int sum = tbb::parallel_reduce(
            tbb::blocked_range<std::size_t>(0ul, data.size(), grain_size), 0,
            [&data] (const tbb::blocked_range<std::size_t>& range, int init) {
                for (std::size_t i = range.begin(); i < range.end(); ++i)
                    init += data[i];
                return init;
            },
            [] (int x, int y) { return x + y; }
    );
    std::cout << "parallel sum = " << sum << std::endl;
    std::cout << "serial sum = " << data.sum() << std::endl;
    return 0;
}
