#include <boost/config.hpp>
#include <boost/graph/adjacency_list.hpp>
#include <boost/graph/dijkstra_shortest_paths.hpp>
#include <boost/graph/graph_traits.hpp>
#include <boost/property_map/property_map.hpp>
#include <iostream>
#include <set>
#include <vector>

using Graph = boost::adjacency_list<boost::listS, boost::vecS,
                                    boost::directedS,
                                    boost::no_property,
                                    boost::property<boost::edge_weight_t,
                                                    double>>;
using Vertex_descr = boost::graph_traits<Graph>::vertex_descriptor;
using Edge = std::pair<int, int>;

Graph read_graph(std::istream& in) {
    std::set<int> vertices;
    std::vector<Edge> edges;
    std::vector<double> weights;
    int vertex1, vertex2;
    double weight;
    while (in >> vertex1 >> vertex2 >> weight) {
        vertices.insert(vertex1);
        vertices.insert(vertex2);
        edges.emplace_back(Edge(vertex1, vertex2));
        weights.push_back(weight);
    }
    Graph graph(edges.cbegin(), edges.cend(), &(weights[0]),
                vertices.size());
    return graph;
}

int main() {
    Graph graph = read_graph(std::cin);
    std::cout << boost::num_vertices(graph) << " vertices" << std::endl;
    boost::graph_traits<Graph>::vertex_iterator vertex, v_end;
    for (std::tie(vertex, v_end) = boost::vertices(graph); vertex != v_end;
            ++vertex)
        std::cout << *vertex << std::endl;
    std::cout << boost::num_edges(graph) << " edges" << std::endl;
    boost::graph_traits<Graph>::edge_iterator edge, e_end;
    for (std::tie(edge, e_end) = boost::edges(graph); edge != e_end;
            ++edge)
        std::cout << boost::source(*edge, graph) << " -> "
                  << boost::target(*edge, graph) << std::endl;
    return 0;
}
