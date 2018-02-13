import plotting_functions as PF                                                                               
import glob                                                                                                   
import re                                                                                                     
import os                                                                                                     
import operator        
import fnmatch 
import math
import numpy as np
from scipy.optimize import curve_fit

def main():
    matches = []
    for root, dirnames, filenames in os.walk('../final_vortices'):
        for filename in fnmatch.filter(filenames, '*.txt'):
            matches.append(os.path.join(root, filename))
    
    dic = dict() 
    for path_file in matches:
        result = re.findall(r"-?\d+\.\d+|-?\d+", path_file)
        N=result[0]
        Lx=result[2]
        Ly=result[3]
        run=result[5]
        cL=result[6]
        itera=result[7]
        key = N + ',' + Lx + ',' + Ly + ',' + cL + ',' + itera
        if key not in dic:
            dic[key] = int(run)
        if key in dic:
            if int(run) > dic[key]:
                dic[key] = int(run) 
    
    print dic

    for path_file in matches:
        #file_name = os.path.split(path_file)[0]
        result = re.findall(r"-?\d+\.\d+|-?\d+", path_file)
        #print path_file
        N=result[0]
        Lx=result[2]
        Ly=result[3]
        run=result[5]
        cL=result[6]
        itera=result[7]
        key = N + ',' + Lx + ',' + Ly + ',' + cL + ',' + itera
        if dic[key] != int(run):
            continue
        print key
        print N
        print Lx
        print Ly
        print run
        print cL
        print itera
        size = int(N)
        
        if size  == 16: 
            continue
        elif size  == 32:
            linear_x = [1.5,3]
        elif size == 48:
            linear_x = [1.5,3]
        elif size  == 40:
            linear_x = [1.5,3]
        elif size == 24:
            continue
        elif size == 64:
            linear_x = [2,3]
        elif size == 128:
            linear_x = [3.5,5]
        directory = "../nv_log/N_" + N + "/dt_0.01/Lx_" + Lx + "Ly_" + Ly 
        if not os.path.exists(directory):
            os.makedirs(directory)
        graph = PF.graph_points(path_file)    
        graph = PF.gr_n(graph, 1)
        graph = PF.gr_n_2(graph, 0)
        graph = PF.normalise(PF.log_div_log, math.log, graph)
        subset_graph = PF.subset_graph(linear_x[0], linear_x[1], graph)     
        times = []     
        num_vor = []     
        PF.split_graph(times, num_vor, subset_graph)     
        popt, pcov = curve_fit(lin,  times, num_vor)
        path=directory+ "/N_" + N + "num_sim_" + run + "cL_" + cL + "iter_" +itera + "exp_" + str(popt[0])+ ".txt"
        PF.write_file(path, graph)

def lin(x, a, b):
    return a*x + b

if __name__ == "__main__":
    main()
