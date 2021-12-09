import numpy as np
from typing import Tuple

def nearest_neighbors(graph: np.ndarray, root: int = 0) -> list:
    solution = []
    curr_node = root
    aux_graph = graph.copy()
    
    for _ in range(len(aux_graph)):
        solution.append(curr_node)
        aux_graph[:, curr_node].fill(np.inf)
        curr_node = np.argmin(aux_graph[curr_node])

    return solution

def compute_solution_cost(graph: np.ndarray, solution: list) -> int:
    cost = 0
    for i in range(len(solution)-1):
        cost += graph[solution[i]][solution[i+1]]

    # Devemos considerar o caminho até a raiz no final da solução (fechando o ciclo)
    cost += graph[solution[-1]][solution[0]]
    return int(cost)

def local_search_2opt(graph: np.ndarray, solution: list, cost: int) -> Tuple[list, int]:
    n = len(graph)
    for i in range(1, n-2):
        for j in range(i+1, n-1):
            # Computando custo de trocar as arestas e verificando potencial melhoria
            old_edges = int(graph[solution[i-1]][solution[i]] + graph[solution[j]][solution[j+1]])
            new_edges = int(graph[solution[i-1]][solution[j]] + graph[solution[i]][solution[j+1]])
            new_cost = (cost - old_edges) + new_edges

            if new_cost < cost:
                # Modificando a solução atual, para isso iremos inverter o sentido das arestas entre i e j e trocar ambos
                new_solution = solution.copy()
                new_solution[i+1:j] = solution[i+1:j][::-1]
                new_solution[i], new_solution[j] = solution[j], solution[i]

                return local_search_2opt(graph, new_solution, new_cost)

    return solution, cost

def simple_swap_sampling(graph: np.ndarray, solution: list, cost: int) -> Tuple[bool, list, int]:
    n = len(graph)
    for i in range(1, n-1):
        for j in range(i+1, n):
            # Construindo nova solução apenas trocando os vértices i e j
            new_solution = solution.copy()
            new_solution[i], new_solution[j] = solution[j], solution[i]
            new_cost = compute_solution_cost(graph, new_solution)

            if new_cost < cost:
                return True, new_solution, new_cost

    return False, solution, cost

def variable_neighborhood_descent(graph: np.ndarray) -> Tuple[list, int]:
    initial_solution = nearest_neighbors(graph)
    initial_cost = compute_solution_cost(graph, initial_solution)

    solution_2opt, cost_2opt = local_search_2opt(graph, initial_solution, initial_cost)
    found, solution, cost = simple_swap_sampling(graph, solution_2opt, cost_2opt)

    while found:
        solution_2opt, cost_2opt = local_search_2opt(graph, solution, cost)
        found, solution, cost = simple_swap_sampling(graph, solution_2opt, cost_2opt)

    return solution, cost
