#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "instance_reader.h"

void my_getline(char *line, int n, FILE *stream) {
    fgets(line, n, stream);
    line[strcspn(line, "\n")] = '\0'; // removendo \n do fgets
}

void read_input_metadata(FILE *file, instance_metadata_t *metadata) {
    char line[BUFSZ];

    my_getline(line, BUFSZ, file);
    while (strcmp(line, "NODE_COORD_SECTION") != 0) {
        char keyword[BUFSZ], value[BUFSZ];
        sscanf(line, " %s %s", keyword, value);

        if (strcmp(keyword, "NAME:") == 0)
            strcpy(metadata->name, value);
        else if (strcmp(keyword, "DIMENSION:") == 0)
            metadata->dimension = atoi(value);
        else if (strcmp(keyword, "EDGE_WEIGHT_TYPE:") == 0)
            strcpy(metadata->edge_weight_type, value);

        my_getline(line, BUFSZ, file);
    }
}

int **build_complete_graph(FILE *file, int n, const char* edge_weight_type) {
    char line[BUFSZ];
    point_t coords[n];
    
    // Lendo as coordenadas dos vértices
    for (int i = 0; i < n; i++) {
        int id;
        double x, y;
        my_getline(line, BUFSZ, file);
        sscanf(line, "%d %lf %lf", &id, &x, &y);

        coords[id-1].x = x;
        coords[id-1].y = y;
    }

    // Criando o grafo completo
    int **graph = (int **) malloc(n * sizeof(int *));
    for (int i = 0; i < n; i++)
        graph[i] = (int *) malloc(n * sizeof(int));

    for (int i = 0; i < n; i++) {
        for (int j = i+1; j < n; j++) {
            int dist = (strcmp(edge_weight_type, "EUC_2D") == 0) ? euclid_2d(coords[i], coords[j]) :
                                                                   pseudo_euclid_2d(coords[i], coords[j]);
            graph[i][j] = dist;
            graph[j][i] = dist;
        }
    }

    // Preenchendo diagonal com infinito (sem conexão do vértice com ele mesmo)
    for (int i = 0; i < n; i++)
        graph[i][i] = INF;

    return graph;
}

int **construct_instance(const char* filename, instance_metadata_t *metadata) {
    FILE *file = fopen(filename, "r");

    read_input_metadata(file, metadata);
    int **graph = build_complete_graph(file, metadata->dimension, metadata->edge_weight_type);
    
    fclose(file);
    return graph;
}

void destroy_complete_graph(int **graph, int n) {
    for (int i = 0; i < n; i++)
        free(graph[i]);

    free(graph);
}