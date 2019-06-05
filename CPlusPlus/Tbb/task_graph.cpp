#include <cstdio>
#include <tbb/tbb.h>

using namespace tbb::flow;

int main() {
    int result = 0;
    graph g;
    broadcast_node<int> input(g);
    function_node<int,int> squarer(g, unlimited,
            [] (int v) -> int { return v*v; });
    function_node<int,int> cuber(g, unlimited,
            [] (int v) -> int { return v*v*v; });
    join_node< tuple<int,int>, queueing> join( g );
    function_node<tuple<int,int>,int> sum(g, serial,
            [&result] (tuple<int,int> v) -> int {
                result += get<0>(v) + get<1>(v);
                return result;
            }
    );
    make_edge(input, squarer);
    make_edge(input, cuber);
    make_edge(squarer, get<0>(join.input_ports()));
    make_edge(cuber, get<1>( join.input_ports()));
    make_edge(join, sum);

    for (int i = 1; i <= 10; ++i)
        input.try_put(i);
    g.wait_for_all();

    printf("Final result is %d\n", result);
    return 0;
}
