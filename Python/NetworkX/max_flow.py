#!/usr/bin/env python

from argparse import ArgumentParser
import networkx as nx
from queue import deque
import random


def create_graph():
    alpha = 3
    beta = 0.5
    G = nx.DiGraph()
    source = 0
    nr_nodes_per_layer = 3
    nr_layers = 2
    sink = nr_nodes_per_layer*nr_layers + 1
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
    arg_parser = ArgumentParser(description='experiment with min-cut')
    options = arg_parser.parse_args()
    G, source, sink = create_graph()
    flow_value, flow_dict = nx.maximum_flow(G, source, sink)
    print('value = {0:.3f}'.format(flow_value))
    print_flow_dict(G, flow_dict)
