from sys import argv
from utils import InstanceReader
from utils.heuristics import variable_neighborhood_descent

if __name__ == '__main__':
    if len(argv) < 2:
        print('usage: python {} <input-file>'.format(argv[0]))
        exit(1)
    
    reader = InstanceReader(argv[1])
    graph = reader.build_complete_graph()

    solution, cost = variable_neighborhood_descent(graph)
    print('Cost:', cost)
    print('Solution:', solution)
