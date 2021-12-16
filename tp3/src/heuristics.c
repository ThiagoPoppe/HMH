#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include "constants.h"
#include "heuristics.h"

int nearest_neighbor(int **graph, int n, int root, int *solution) {
    int cost = 0;
    int visited[n];
    int curr_node = root;

    visited[curr_node] = 1;
    for (int i = 1; i < n; i++)
        visited[i] = 0;

    solution[0] = curr_node;
    for (int i = 1; i < n; i++) {
        int next_node = pick_nearest_neighbor(graph, n, curr_node, visited);

        solution[i] = next_node;
        cost += graph[curr_node][next_node];
        
        visited[next_node] = 1;
        curr_node = next_node;
    }

    // Devemos incluir o custo de ir do último vértice para o primeiro
    cost += graph[solution[n-1]][solution[0]];
    return cost;
}

int pick_nearest_neighbor(int **graph, int n, int v, int *visited) {
    int nn = -1;
    int min_dist = INF;

    for (int i = 0; i < n; i++) {
        if (!visited[i] && graph[v][i] < min_dist) {
            nn = i;
            min_dist = graph[v][i];
        }
    }

    if (nn == -1) {
        printf("error: couldn't find nearest neighbor");
        exit(1);
    }

    return nn;
}

void swap(int *array, int i, int j) {
    int aux = array[i];
    array[i] = array[j];
    array[j] = aux;
}

void invert_edges(int *solution, int i, int j) {
    while (i < j) {
        swap(solution, i, j);
        i++; j--;
    }
}

int compute_solution_cost(int **graph, int n, int *solution) {
    int cost = 0;
    for (int i = 0; i < n-1; i++)
        cost += graph[solution[i]][solution[i+1]];

    cost += graph[solution[n-1]][solution[0]];
    return cost;
}

int local_search_2opt(int **graph, int n, int *solution, int cost) {
    for (int i = 1; i < n-2; i++) {
        for (int j = i+1; j < n-1; j++) {
            // Computando custo de trocar as arestas e verificando se há melhoria
            int old_edges_cost = graph[solution[i-1]][solution[i]] + graph[solution[j]][solution[j+1]];
            int new_edges_cost = graph[solution[i-1]][solution[j]] + graph[solution[i]][solution[j+1]];
            int new_cost = (cost - old_edges_cost) + new_edges_cost;

            if (new_cost < cost) {
                // Modificando a solução atual, para isso iremos inverter o sentido das arestas entre i e j (inclusos)
                invert_edges(solution, i, j);
                return local_search_2opt(graph, n, solution, new_cost);
            }
        }
    }

    // Não achamos nenhuma melhoria
    return cost;
}

int simple_swap_sampling(int **graph, int n, int *solution, int cost) {
    for (int i = 1; i < n-1; i++) {
        for (int j = i+1; j < n; j++) {
            // Construindo nova solução apenas trocando os vértices i e j
            swap(solution, i, j);

            int new_cost = compute_solution_cost(graph, n, solution);
            if (new_cost < cost)
                return new_cost;

            // Voltando para a solução anterior
            swap(solution, i, j);
        }
    }

    return cost;
}

int variable_neighborhood_descent(int **graph, int n, int *solution, int cost) {
    int cost_2opt = local_search_2opt(graph, n, solution, cost);
    int cost_2swap = simple_swap_sampling(graph, n, solution, cost_2opt);

    while (cost_2swap != cost_2opt) {
        cost_2opt = local_search_2opt(graph, n, solution, cost_2swap);
        cost_2swap = simple_swap_sampling(graph, n, solution, cost_2opt);
    }

    return cost_2opt;
}

void get_minmax_costs(int *costs, int *visited, int n, int *min_cost, int *max_cost) {
    int c_max = -1;
    int c_min = INF;

    for (int i = 0; i < n; i++) {
        if (!visited[i]) {
            if (costs[i] < c_min)
                c_min = costs[i];
            if (costs[i] > c_max)
                c_max = costs[i];
        }
    }

    (*min_cost) = c_min;
    (*max_cost) = c_max;
}

int randomized_nearest_neighbors(int **graph, int n, int root, int *solution, double alpha) {
    int cost = 0;
    int visited[n];
    int curr_node = root;

    visited[curr_node] = 1;
    for (int i = 1; i < n; i++)
        visited[i] = 0;

    solution[0] = curr_node;
    for (int i = 1; i < n; i++) {
        int next_node = pick_random_nearest_neighbor(graph, n, curr_node, visited, alpha);

        solution[i] = next_node;
        cost += graph[curr_node][next_node];
        
        visited[next_node] = 1;
        curr_node = next_node;
    }

    // Devemos incluir o custo de ir do último vértice para o primeiro
    cost += graph[solution[n-1]][solution[0]];
    return cost;
}

int pick_random_nearest_neighbor(int **graph, int n, int v, int *visited, double alpha) {
    int c_min, c_max;
    get_minmax_costs(graph[v], visited, n, &c_min, &c_max);
    
    int rcl[n];
    int n_candidates = 0;
    int threshold = c_min + alpha * (c_max - c_min);

    // Construindo a lista restrita de candidatos (RCL)
    for (int i = 0; i < n; i++) {
        if (!visited[i] && graph[v][i] <= threshold) {
            rcl[n_candidates] = i;
            n_candidates++;
        }
    }

    if (n_candidates == 0) {
        printf("error: couldn't find any nearest neighbor\n");
        exit(1);
    }

    // Retornando algum vizinho aleatório da RCL
    return rcl[rand() % n_candidates];
}

int grasp(int **graph, int n, int root, int *solution, int n_iter, double alpha) {
    int best_cost = INF;
    int aux_solution[n];

    srand(time(NULL));
    for (int iter = 0; iter < n_iter; iter++) {
        int cost = randomized_nearest_neighbors(graph, n, root, aux_solution, alpha);
        cost = variable_neighborhood_descent(graph, n, aux_solution, cost);

        if (cost < best_cost) {
            best_cost = cost;
            for (int i = 0; i < n; i++)
                solution[i] = aux_solution[i];
        }
    }

    return best_cost;
}