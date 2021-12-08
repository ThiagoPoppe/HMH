import numpy as np


def nearest_neighbors(graph: np.ndarray, root: int = 0) -> list:
    solution = []
    curr_node = root
    aux_graph = graph.copy()
    
    for _ in range(len(aux_graph)):
        solution.append(curr_node)
        aux_graph[:, curr_node].fill(np.inf)

        curr_node = np.argmin(aux_graph[curr_node])

    # Adicionando a raiz no final da solução (fechando o ciclo)
    solution.append(root)
    return solution


def compute_solution_cost(graph: np.ndarray, solution: list) -> int:
    cost = 0
    for i in range(len(solution)-1):
        cost += graph[solution[i]][solution[i+1]]

    return int(cost)