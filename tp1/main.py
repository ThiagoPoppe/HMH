from sys import argv
from typing import List

import numpy as np

from utils.instance import TSPInstance

def get_nearest_neighbor(v: int, instance: np.ndarray, solution: List[int]) -> int:
    min_value = np.inf
    nearest_neighbor = -1
    
    for i in range(len(instance)):
        if i not in solution and instance[v][i] < min_value:
            min_value = instance[v][i]
            nearest_neighbor = i

    return nearest_neighbor

def heuristic(instance: np.ndarray, v: int = 0) -> List[int]:
    solution = [v]
    for _ in range(len(instance) - 1):
        next_node = get_nearest_neighbor(v, instance, solution)
        solution.append(next_node)
        v = next_node

    # Adicionando a raiz para completar o ciclo
    return solution + [solution[0]]

def compute_path_cost(instance: np.ndarray, nodes: List[int]) -> float:
    cost = 0.0
    for i in range(len(nodes) - 1):
        cost += instance[nodes[i]][nodes[i+1]]

    return cost

if __name__ == '__main__':
    if len(argv) != 2:
        print('usage: python {} <input-file>'.format(argv[0]))
        exit(1)

    instance = TSPInstance(filename=argv[1]).get_instance_as_adj_matrix()
    solution = heuristic(instance)

    print('Cost of solution:', compute_path_cost(instance, solution))
    print('Solution found by heuristic:', solution)
