#!/usr/bin/env python

from argparse import ArgumentParser
import networkx as nx
import random


def create_graph(nr_nodes_per_layer=3):
    alpha = 3
    beta = 0.5
    G = nx.DiGraph()
    source = 0
    sink = 2*nr_nodes_per_layer + 1
    fmt_str = 'capacity {0} -> {1}: {2:.3f}'
# from source to first layter
    for i in range(1, nr_nodes_per_layer + 1):
        capacity = random.gammavariate(alpha, beta)
        G.add_edge(source, i, capacity=capacity)
        print(fmt_str.format(source, i, capacity))
# from layter 1 to layer 2
    for i in range(1, nr_nodes_per_layer + 1):
        j = i + nr_nodes_per_layer
        capacity = random.gammavariate(alpha, beta)
        G.add_edge(i, j, capacity=capacity)
        print(fmt_str.format(i, j, capacity))
# rom layer 2 to sink
    for i in range(nr_nodes_per_layer + 1, 2*nr_nodes_per_layer + 1):
        capacity = random.gammavariate(alpha, beta)
        G.add_edge(i, sink, capacity=capacity)
        print(fmt_str.format(i, sink, capacity))
    return G, source, sink


def print_flow_dict(G, flow_dict):
    for edge in G.edges_iter():
        i, j = edge
        print('flow {0} -> {1}: {2:.3f}'.format(i, j, flow_dict[i][j]))

if __name__ == '__main__':
    arg_parser = ArgumentParser(description='experiment with maximum flow '
                                            'algorithm')
    arg_parser.add_argument('--n', type=int, help='number of nodes/layer')
    options = arg_parser.parse_args()
    G, source, sink = create_graph(options.n)
    flow_value, flow_dict = nx.maximum_flow(G, source, sink)
    print('value = {0:.3f}'.format(flow_value))
    print_flow_dict(G, flow_dict)
