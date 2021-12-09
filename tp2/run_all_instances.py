import time
from glob import glob
from utils import InstanceReader
from utils.heuristics import variable_neighborhood_descent

if __name__ == '__main__':
    files = glob('tsp_instances/*.tsp')
    files.extend(glob('tsp_instances/EUC_2D/*.tsp'))

    print('instância,número de cidades,tempo de execução,custo da solução (VND),distância utilizada')
    for filename in files:
        reader = InstanceReader(filename)
        graph = reader.build_complete_graph()

        begin = time.time()
        solution, cost = variable_neighborhood_descent(graph)
        end = time.time()

        distance_type = 'pseudo-euclidiana' if reader.distance_type == 'ATT' else 'euclidiana 2D'
        print('{},{},{:.2f},{},{}'.format(reader.instance_name, reader.dimension, end-begin, cost, distance_type))
