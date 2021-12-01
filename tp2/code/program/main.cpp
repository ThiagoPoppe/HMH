#include <iostream>
#include "instance_reader.hpp"

using namespace std;

int get_nearest_neighbor(int v, graph_t &graph, vector<int> &solution) {
    int nearest_id = -1;
    int min_distance = INF;

    for (int i = 0; i < graph.size(); i++) {
        if (i == v) // não analisaremos o vértice com ele mesmo
            continue;

        // Verificando se já analisamos esse vértice
        bool has_visited = false;
        for (int j = 0; j < solution.size(); j++) {
            if (solution[j] == i) {
                has_visited = true;
                break;
            }
        }

        if (!has_visited && graph[v][i] < min_distance) {
            nearest_id = i;
            min_distance = graph[v][i];
        }
    }

    if (nearest_id == -1) {
        cout << "error: couldn't find a nearest neighbor";
        exit(1);
    }

    return nearest_id;
}

vector<int> nearest_neighbors(graph_t &graph) {
    vector<int> solution;
    solution.push_back(0);

    for (int i = 0; i < graph.size() - 1; i++) {
        int nearest_id = get_nearest_neighbor(solution[i], graph, solution);
        solution.push_back(nearest_id);
    }

    // Fechando o ciclo adicionando o vértice inicial
    solution.push_back(0);
    return solution;
}

int compute_solution_cost(graph_t &graph, vector<int> &solution) {
    int cost = 0;
    for (int i = 0; i < solution.size() - 1; i++)
        cost += graph[solution[i]][solution[i+1]];

    return cost;
}

int main(int argc, const char **argv) {
    if (argc != 2) {
        cout << "usage: " << argv[0] << " <input-file>" << endl;
        exit(1);
    }

    string filename = string(argv[1]);
    InstanceReader reader = InstanceReader(filename);
    graph_t graph = reader.read_instance();
    
    // Rodando nossa heurística
    vector<int> solution = nearest_neighbors(graph);
    int cost = compute_solution_cost(graph, solution);

    cout << "cost: " << cost << endl;
    cout << "solution: ";
    for (int i = 0; i < solution.size(); i++)
        cout << solution[i] << " ";
    cout << endl;

    return 0;
}