from tqdm import tqdm
from glob import glob
from utils import InstanceReader
from utils.heuristics import compute_solution_cost, nearest_neighbors, local_search_2opt, variable_neighborhood_descent

if __name__ == '__main__':
    files = glob('tsp_instances/*.tsp')
    files.extend(glob('tsp_instances/EUC_2D/*.tsp'))

    print('instância,número de cidades,custo da solução (NN),custo da solução (2-OPT),custo da solução (VND)')
    for filename in tqdm(files):
        reader = InstanceReader(filename)
        graph = reader.build_complete_graph()

        nn_solution = nearest_neighbors(graph)
        nn_cost = compute_solution_cost(graph, nn_solution)
        _, opt2_cost = local_search_2opt(graph, nn_solution, nn_cost)
        _, vnd_cost = variable_neighborhood_descent(graph)
        
        distance_type = 'pseudo-euclidiana' if reader.distance_type == 'ATT' else 'euclidiana 2D'
        print('{},{},{},{},{}'.format(reader.instance_name, reader.dimension, nn_cost, opt2_cost, vnd_cost))
