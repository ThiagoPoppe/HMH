#include <iostream>
#include <sstream>
#include <fstream>
#include <cmath>

#include "instance_reader.hpp"

using namespace std;

InstanceReader::InstanceReader(string filename) {
    this->filename = filename;
}

int InstanceReader::calculate_euclidean_distance(point_t u, point_t v) {
    double dx = u.first - v.first;
    double dy = u.second - v.second;

    return round(sqrt(dx*dx + dy*dy));
}

int InstanceReader::calculate_pseudo_euclidean_distance(point_t u, point_t v) {
    double dx = u.first - v.first;
    double dy = u.second - v.second;

    double real_dist = sqrt((dx*dx + dy*dy) / 10.0);
    int rounded_dist = round(real_dist);

    if (rounded_dist < real_dist)
        return rounded_dist + 1;

    return rounded_dist;
}

graph_t InstanceReader::read_instance() {
    string line;
    ifstream file(this->filename);
    
    // Lendo cada linha do arquivo até NODE_COORD_SECTION salvando as dimensões e tipo de peso
    while (getline(file, line)) {
        if (line == "NODE_COORD_SECTION")
            break;

        string keyword, value;
        stringstream stream(line);

        stream >> keyword >> value;
        if (keyword == "NAME:")
            this->instance_name = value;

        else if (keyword == "TYPE:") {
            if (value != "TSP") {
                cout << "error: instance type must be TSP" << endl;
                exit(1);
            }
        }

        else if (keyword == "DIMENSION:")
            this->dimension = stoi(value);

        else if (keyword == "EDGE_WEIGHT_TYPE:") {
            if (value != "EUC_2D" && value != "ATT") {
                cout << "error: edge weight type must be either EUC_2D or ATT" << endl;
                exit(1);
            }

            this->edge_weight_type = value;
        }
    }

    // Lendo cada coordenada da nossa instância
    coords_t coords(this->dimension);
    for (int i = 0; i < this->dimension; i++) {
        int id;
        double x, y;

        getline(file, line);
        stringstream stream(line);

        stream >> id >> x >> y;
        coords[i] = make_pair(x, y);
    }

    // Criando grafo baseado nas coordenadas e tipo de peso das arestas
    graph_t graph(this->dimension, vector<double>(this->dimension));
    for (int i = 0; i < this->dimension; i++) {
        for (int j = i+1; j < this->dimension; j++) {
            if (this->edge_weight_type == "EUC_2D")
                graph[i][j] = graph[j][i] = this->calculate_euclidean_distance(coords[i], coords[j]);

            else
                graph[i][j] = graph[j][i] = this->calculate_pseudo_euclidean_distance(coords[i], coords[j]);   
        }
    }

    // Definindo a diagonal da matriz como infinito (não há aresta de um vértice para ele mesmo)
    for (int i = 0; i < this->dimension; i++)
        graph[i][i] = INF;

    file.close();
    return graph;
}