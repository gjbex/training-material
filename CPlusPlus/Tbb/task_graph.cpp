#include <cstdio>
#include <tbb/tbb.h>

using namespace tbb::flow;

struct Square {
    int operator()(int v) { return v*v; }
};

struct Cube {
    int operator()(int v) { return v*v*v; }
};

class Sum {
    int &sum_;
    public:
    Sum( int& sum) : sum_(sum) {}
    int operator()( tuple< int, int > v ) {
        sum_ += get<0>(v) + get<1>(v);
        return sum_;
    }
};

int main() {
    int result = 0;

    graph g;
    broadcast_node<int> input(g);
    function_node<int,int> Squarer(g, unlimited, Square());
    function_node<int,int> Cuber(g, unlimited, Cube());
    join_node< tuple<int,int>, queueing> join( g );
    function_node<tuple<int,int>,int> sum(g, serial, Sum(result));

    make_edge(input, Squarer);
    make_edge(input, Cuber);
    make_edge(Squarer, get<0>(join.input_ports()));
    make_edge(Cuber, get<1>( join.input_ports()));
    make_edge(join, sum);

    for (int i = 1; i <= 10; ++i)
        input.try_put(i);
    g.wait_for_all();

    printf("Final result is %d\n", result);
    return 0;
}
