import math

def graph_points(file_name):
    graph = []
    with open(file_name,'r') as file:                         
        for line in file.readlines():
            l = line.strip().split(' ')
            graph.append([float(l[0]), float(l[1])])
    return graph 

def normalise(f1, f2, graph):
    for point in graph:
        point[0] = f1(point[0])
        point[1] = f2(point[1])
    return graph

def div_log(t):
    return t/math.log(t)

def log_div_log(t):
    return math.log(div_log(t))

def iden(t):
    return t

def subset_graph(x1, x2, graph):
    subset = [[point[0], point[1]] for point in graph if                                                
                (point[0] > x1) and (point[0] < x2)]
    return subset

def split_graph(first, second, graph):
    for point in graph:
        first.append(point[0])
        second.append(point[1])

def gr_n(graph, n):
    gr_n_graph = []
    for point in graph:
        if point[0] > n:
            gr_n_graph.append(point)
    return gr_n_graph
