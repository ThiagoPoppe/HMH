#ifndef INSTANCE_READER_H
#define INSTANCE_READER_H

#include "point.h"
#include "constants.h"
#include "distances.h"

typedef struct {
    int dimension;
    char name[BUFSZ];
    char edge_weight_type[BUFSZ];
} instance_metadata_t;

void my_getline(char *line, int n, FILE *stream);
void read_input_metadata(FILE *file, instance_metadata_t *metadata);
int **build_complete_graph(FILE *file, int n, const char* edge_weight_type);
int **construct_instance(const char* filename, instance_metadata_t *metadata);
void destroy_complete_graph(int **graph, int n);

#endif