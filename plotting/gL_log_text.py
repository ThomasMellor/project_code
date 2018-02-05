import plotting_functions as PF                                                                               
import glob                                                                                                   
import re                                                                                                     
import os                                                                                                     
import operator        
import fnmatch 

matches = []
for root, dirnames, filenames in os.walk('../final_binder_cumulant'):
    for filename in fnmatch.filter(filenames, '*.txt'):
        matches.append(os.path.join(root, filename))

for path_file in matches:
    #file_name = os.path.split(path_file)[0]
    result = re.findall(r"-?\d+\.\d+|\d+", path_file)
    if( int(result[4]) == 2 or int(result[4]) == 4):
        continue 
    print path_file
    N=result[0]
    Lx=result[2]
    Ly=result[3]
    run=result[5]
    cL=result[6]
    itera=result[7]
    print N
    print Lx
    print Ly
    print run
    print cL
    print itera
    directory = "../gL_log/N_" + N + "/dt_0.01/Lx_" + Lx + "Ly_" + Ly 
    print directory 
    if not os.path.exists(directory):
        os.makedirs(directory)
    graph = PF.graph_points(path_file)    
    graph = PF.gr_n(graph, 1)                                                                                     
    graph = PF.normalise(lambda t : PF.div_log(t)/(int(N)**2), lambda x : x, graph)
    path=directory+ "/N_" + N + "num_sim_" + run + "cL_" + cL + "iter_" +itera + ".txt"
    PF.write_file(path, graph)
