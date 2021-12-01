#ifndef INSTANCE_READER
#define INSTANCE_READER

#include <string>
#include <vector>

using namespace std;

typedef pair<double, double> point_t;
typedef vector<point_t> coords_t;
typedef vector<vector<double>> graph_t;

#define INF 0x3f3f3f3f

class InstanceReader {
private:
    string filename;

private:
    int dimension;
    string instance_name;
    string edge_weight_type;

private:
    int calculate_euclidean_distance(point_t u, point_t v);
    int calculate_pseudo_euclidean_distance(point_t u, point_t v);

public:
    InstanceReader(string filename);
    ~InstanceReader() { }

    int get_dimension() { return this->dimension; }
    string get_instance_name() { return this->instance_name; }
    string get_edge_weight_type() { return this->edge_weight_type; }

    graph_t read_instance();
};

#endif