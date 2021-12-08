import numpy as np
from typing import List

from .types import Point
from .distances import calculate_euclidean_distance
from .distances import calculate_pseudo_euclidean_distance


class InstanceReader:
    def __init__(self, filename: str) -> None:
        with open(filename, 'r') as f:
            line = f.readline()

            while line.strip() != "NODE_COORD_SECTION":
                keyword, value = line.split(':')
                value = value.strip()

                if keyword == "NAME":
                    self.instance_name = value
                
                elif keyword == "DIMENSION":
                    self.n_nodes = int(value)
                
                elif keyword == "EDGE_WEIGHT_TYPE":
                    self.distance = calculate_euclidean_distance
                    if value == "ATT":
                        self.distance = calculate_pseudo_euclidean_distance

                line = f.readline()

            # Anotando as coordenadas
            self.coords: List[Point] = []
            for _ in range(self.n_nodes):
                _, x, y = f.readline().split()
                self.coords.append(Point(float(x), float(y)))
    

    def build_complete_graph(self) -> np.ndarray:
        graph = np.zeros((self.n_nodes, self.n_nodes))

        for i in range(self.n_nodes):
            for j in range(i+1, self.n_nodes):
                graph[i][j] = self.distance(self.coords[i], self.coords[j])
                graph[j][i] = graph[i][j]

        np.fill_diagonal(graph, np.inf)
        return graph
