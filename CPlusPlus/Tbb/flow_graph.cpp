#include <cstdio>
#include <tbb/tbb.h>
#include <tuple>

int main() {
    int result = 0;
    tbb::flow::graph graph;
    tbb::flow::broadcast_node<int> input(graph);
    tbb::flow::function_node<int,int> squarer(graph, tbb::flow::unlimited,
            [] (int v) -> int { return v*v; });
    tbb::flow::function_node<int,int> cuber(graph, tbb::flow::unlimited,
            [] (int v) -> int { return v*v*v; });
    tbb::flow::join_node< std::tuple<int,int>, tbb::flow::queueing> join(graph);
    tbb::flow::function_node<std::tuple<int,int>,int> sum(graph, tbb::flow::serial,
            [&result] (std::tuple<int,int> v) -> int {
                result += std::get<0>(v) + std::get<1>(v);
                return result;
            }
    );
    make_edge(input, squarer);
    make_edge(input, cuber);
    make_edge(squarer, std::get<0>(join.input_ports()));
    make_edge(cuber, std::get<1>( join.input_ports()));
    make_edge(join, sum);

    for (int i = 1; i <= 10; ++i)
        input.try_put(i);
    graph.wait_for_all();

    printf("Final result is %d\n", result);
    return 0;
}
