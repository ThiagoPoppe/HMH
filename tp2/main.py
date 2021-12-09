import numpy as np
from sys import argv
from utils import InstanceReader
from utils.heuristics import (
    nearest_neighbors,
    compute_solution_cost,
    local_search_2opt
)

if __name__ == '__main__':
    if len(argv) < 2:
        print('usage: python {} <input-file>'.format(argv[0]))
        exit(1)
    
    reader = InstanceReader(argv[1])
    graph = reader.build_complete_graph()

    solution = nearest_neighbors(graph)
    cost = compute_solution_cost(graph, solution)
    print('Solution (NN):', solution)
    print('Cost (NN):', cost)

    solution, cost = local_search_2opt(graph, solution, cost)
    print('\nSolution (2-OPT):', solution)
    print('Cost (2-OPT):', cost)
