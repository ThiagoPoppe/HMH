#ifndef HEURISTICS_H
#define HEURISTICS_H

int nearest_neighbor(int **graph, int n, int root, int *solution);
int pick_nearest_neighbor(int **graph, int n, int v, int *visited);

void swap(int *array, int i, int j);
void invert_edges(int *solution, int begin, int end);
int compute_solution_cost(int **graph, int n, int *solution);
int local_search_2opt(int **graph, int n, int *solution, int cost);
int simple_swap_sampling(int **graph, int n, int *solution, int cost);
int variable_neighborhood_descent(int **graph, int n, int *solution, int cost);

void get_minmax_costs(int *costs, int *visited, int n, int *c_min, int *c_max);
int randomized_nearest_neighbors(int **graph, int n, int root, int *solution, double alpha);
int pick_random_nearest_neighbor(int **graph, int n, int v, int *visited, double alpha);
int grasp(int **graph, int n, int root, int *solution, int n_iter, double alpha);

#endif