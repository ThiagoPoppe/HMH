import numpy as np
import networkx as nx

from .distances import euclidean2D_distance
from .distances import pseudo_eclidean2D_distance

class TSPInstance:
    def __init__(self, filename: str, debug: bool = False) -> None:
        with open(filename, 'r') as f:
            line = f.readline()

            # Processando o cabeçalho do arquivo
            self._header = dict()
            while line.strip() != 'NODE_COORD_SECTION':
                key = line.split(':')[0].strip()
                self._header[key] = ' '.join(line.split(':')[1:]).strip()

                if key == 'DIMENSION':
                    self._header[key] = int(self._header[key])

                line = f.readline()

            self._validate_header()
            if debug:
                self._log_header()

            # Processando as coordenadas do arquivo
            self._coords = list()
            for _ in range(self._header['DIMENSION']):
                _, x, y = f.readline().split()
                self._coords.append((float(x), float(y)))

            # Definindo a função de distância
            self._dist_function = euclidean2D_distance
            if self._header['EDGE_WEIGHT_TYPE'] == 'ATT':
                self._dist_function = pseudo_eclidean2D_distance

    def get_instance_as_graph(self) -> nx.Graph:
        graph = nx.Graph()
        n_nodes = self._header['DIMENSION']

        for i in range(0, n_nodes):
            for j in range(i+1, n_nodes):
                graph.add_edge(i, j, weight=self._dist_function(self._coords[i], self._coords[j]))

        return graph

    def get_instance_as_adj_matrix(self) -> np.ndarray:
        n_nodes = self._header['DIMENSION']
        matrix = np.zeros((n_nodes, n_nodes))

        for i in range(0, n_nodes):
            for j in range(i+1, n_nodes):
                matrix[i][j] = self._dist_function(self._coords[i], self._coords[j])
                matrix[j][i] = self._dist_function(self._coords[j], self._coords[i])
        
        # Um vértice não possui conexões com ele mesmo!
        # Logo, a distância deve ser infinita
        np.fill_diagonal(matrix, np.inf)

        return matrix

    def _validate_header(self) -> None:
        if 'TYPE' not in self._header:
                raise KeyError('TYPE key missing from file')
        if 'DIMENSION' not in self._header:
                raise KeyError('DIMENSION key missing from file')
        if 'EDGE_WEIGHT_TYPE' not in self._header:
                raise KeyError('EDGE_WEIGHT_TYPE key missing from file')
        if self._header['TYPE'] != 'TSP':
            raise ValueError('Instance type must be TSP')
        if self._header['EDGE_WEIGHT_TYPE'] not in ('EUC_2D', 'ATT'):
            raise ValueError('EDGE_WEIGHT_TYPE must be either EUC_2D or ATT')

    def _log_header(self) -> None:
        print('File self._header information:')
        for key in self._header:
            print(' - {}: {}'.format(key, self._header[key]))