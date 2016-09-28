# NetworkX
NetworkX is an excellent library that implements graph representations
and algorithms.  Note is is not part of Python's standard library.

## What is it?
1. `generate_random_tree.py`: illustration of how to use the NetworkX
   DiGraph class to represent a tree, generates a random tree according
   to specifications
1. `add_random_weights.py`: reads a GraphML representation of a tree, and
   addds random weights to the edges
1. `compute_leaf_path_length.py`: compute the length of all paths from the
   tree's root to each of the leaves
1. `par_compute_leaf_length.py`: compute the length of all paths
   from the tree's root to each of the leaves, uses `multiprocessing` for
   parallel processing
1. `graph.xml`: example GraphML representation of a tree
1. `graph.txt`: example edge list representation of a tree
1. `weighted_tree.xml`: example GraphML representation of a weighted tree
1. `max_flow.py`: illustration of the maximum flow algorithm on a very
    simple case of three parallel flows.
1. `shortest_path.ipynb`: Jupyter notebook illustrating the shortest path
    algorithm.
