#include <boost/coroutine2/all.hpp>
#include <iostream>

using coro_t = boost::coroutines2::coroutine<int>;

int main(int argc, char* argv[]) {
    int limit {10};
    if (argc > 1)
        limit = std::stoi(argv[1]);
    coro_t::pull_type range(
            boost::coroutines2::fixedsize_stack(),
            [limit] (coro_t::push_type& yield) {
                for (int i = 0; i < limit; ++i)
                    yield(i);
            }
    );
    for (auto& value: range)
        std::cout << value << std::endl;
    return 0;
}
