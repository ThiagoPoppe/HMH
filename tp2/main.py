from sys import argv
from utils import InstanceReader
from utils.heuristics import (
    nearest_neighbors,
    compute_solution_cost
)


if __name__ == '__main__':
    if len(argv) < 2:
        print('usage: python {} <input-file>'.format(argv[0]))
        exit(1)
    
    reader = InstanceReader(argv[1])
    graph = reader.build_complete_graph()

    solution = nearest_neighbors(graph)
    cost = compute_solution_cost(graph, solution)

    print('Cost:', cost)
    print('Solution:', solution)
