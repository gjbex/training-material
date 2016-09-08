#include <boost/config.hpp>
#include <boost/graph/graph_traits.hpp>
#include <boost/graph/adjacency_list.hpp>
#include <boost/graph/topological_sort.hpp>
#include <iostream>

// type definitions to conveniently work with Boost graphs
typedef std::pair<int, int> Edge;
typedef boost::adjacency_list<boost::vecS, boost::vecS,
                              boost::bidirectionalS> Graph;
typedef boost::graph_traits<Graph>::vertex_descriptor Vertex;
typedef boost::property_map<Graph, boost::vertex_index_t> Index_map;
typedef boost::graph_traits<Graph>::vertex_iterator Vertex_iter;

// type definitions for auxilery data structures
typedef std::list<std::string> Name_list;
typedef std::unordered_map<int, std::string> Id_map;
typedef std::unordered_map<std::string, int> Name_map;
typedef std::pair<Id_map, Name_map> Maps;

Maps& create_maps(const Name_list& names);
void print_vertices(const Graph& grapph, const Name_map& name_map);

// names of the family members
const Name_list names = {
    "Alice", "Bob", "Carol", "Dave", "Eve"
};

int main(int argc, char *argv[]) {
    std::size_t nr_vertices = names.size();
    // for convenience, map between numerical IDs/names, and vice versa
    Maps maps = create_maps(names);
    Id_map id_map = maps.first;
    Name_map name_map = maps.second;
    // define the graph's edges as an array, and determine the number of
    // edges
    Edge is_child_of[] = {
        Edge(name_map["Carol"], name_map["Alice"]),
        Edge(name_map["Carol"], name_map["Bob"]),
        Edge(name_map["Eve"],   name_map["Alice"]),
        Edge(name_map["Eve"],   name_map["Dave"])
    };
    const std::size_t nr_edges = sizeof(is_child_of)/sizeof(Edge);
    // create the graph, based on the array of edges
    Graph g(is_child_of, is_child_of + nr_edges, nr_vertices);
    // perform a topological sort, and store the vertices in a list, print
    // it
    std::list<Vertex> family_lines;
    boost::topological_sort(g, std::front_inserter(family_lines));
    for (auto it = family_lines.begin(); it != family_lines.end(); it++)
        std::cout << id_map[*it] << std::endl;
    // print all vertices
    Index_map index_map = boost::get(Vertex_index, g); 
    std::pair<Vertex_iter, Vertex_iter> iters;
    for (iters = boost::vertices(g); iters.first != iters.second;
            iters.first++) {
        Vertex v = *iters.first;
        std::cout << index_map[v] << std::endl;
    }
    return 0;
}

Maps& create_maps(const Name_list& names) {
    Id_map id_map;
    Name_map name_map;
    int id = 0;
    for (auto it = names.begin(); it != names.end(); it++) {
        std::string name = *it;
        id_map[id] = name;
        name_map[name] = id;
        id++;
    }
    Maps *maps = new Maps(id_map, name_map);
    return *maps;
}

void print_vertices(const Graph& grapph, const Name_map& name_map) {
    
}
