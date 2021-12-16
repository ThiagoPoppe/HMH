#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include "heuristics.h"
#include "instance_reader.h"

int n_files = 21;
char *files[] = {
    "tsp_instances/att48.tsp",
    "tsp_instances/EUC_2D/berlin52.tsp",
    "tsp_instances/EUC_2D/kroA100.tsp",
    "tsp_instances/EUC_2D/kroA150.tsp",
    "tsp_instances/EUC_2D/kroA200.tsp",
    "tsp_instances/EUC_2D/kroB100.tsp",
    "tsp_instances/EUC_2D/kroB150.tsp",
    "tsp_instances/EUC_2D/kroB200.tsp",
    "tsp_instances/EUC_2D/kroC100.tsp",
    "tsp_instances/EUC_2D/kroD100.tsp",
    "tsp_instances/EUC_2D/kroE100.tsp",
    "tsp_instances/EUC_2D/lin105.tsp",
    "tsp_instances/EUC_2D/pr107.tsp",
    "tsp_instances/EUC_2D/pr124.tsp",
    "tsp_instances/EUC_2D/pr136.tsp",
    "tsp_instances/EUC_2D/pr144.tsp",
    "tsp_instances/EUC_2D/pr152.tsp",
    "tsp_instances/EUC_2D/pr76.tsp",
    "tsp_instances/EUC_2D/rat195.tsp",
    "tsp_instances/EUC_2D/rat99.tsp",
    "tsp_instances/EUC_2D/st70.tsp"
};

int main(int argc, char const *argv[]) {
    if (argc != 3) {
        printf("usage: %s <n-iter> <alpha>\n", argv[0]);
        exit(1);
    }

    int n_iter = atoi(argv[1]);
    double alpha = atof(argv[2]);

    printf("instância,número de cidades,tempo de execução,custo da solução (GRASP),distância utilizada\n");
    for (int i = 0; i < n_files; i++) {
        clock_t begin = clock();
        instance_metadata_t metadata;
        int **graph = construct_instance(files[i], &metadata);

        int solution[metadata.dimension];
        int cost = grasp(graph, metadata.dimension, 0, solution, n_iter, alpha);
        clock_t end = clock();

        double exec_time = (double) (end - begin) / CLOCKS_PER_SEC;
        printf("%s,%d,%.2f,%d,%s\n", metadata.name, metadata.dimension, exec_time, cost, metadata.edge_weight_type);
        destroy_complete_graph(graph, metadata.dimension);
    }

    return 0;
}
