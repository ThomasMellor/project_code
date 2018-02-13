import math

def graph_points(file_name):
    graph = []
    with open(file_name,'r') as doc:                         
        for line in doc.readlines():
            l = line.strip().split(' ')
            graph.append([float(l[0]), float(l[1])])
    return graph 

def write_file(file_name, data):
    with open(file_name,'w') as doc:
        for l in data:
            doc.write(str(l[0]))
            doc.write(' ')
            doc.write(str(l[1]))
            doc.write('\n')

def append_file(file_name, data):
    with open(file_name, 'a+') as doc:
        for l in data:
            print l 
            doc.write(str(l[0]))                                                                             
            doc.write(' ')                                                                                   
            doc.write(str(l[1]))                                                                             
            doc.write('\n')

def normalise(f1, f2, graph):
    for point in graph:
        point[0] = f1(point[0])
        point[1] = f2(point[1])
    return graph

def div_log(t):
    return t/math.log(t)

def log_div_log(t):
    return math.log(div_log(t))

def subset_graph(x1, x2, graph):
    subset = []
    for point in graph:
        if point[0] > x1 and point[0] < x2:
            subset.append(point)
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

def gr_n_2(graph, n):
    gr_n_graph = []
    for point in graph:
        if point[1] > n:
            gr_n_graph.append(point)
    return gr_n_graph
