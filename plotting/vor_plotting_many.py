import numpy as np
import matplotlib.pyplot as plt
import math
from scipy.optimize import curve_fit
import plotting_functions as PF
import glob
import os
import re
import operator

def main():
    files = glob.glob("../vortices/N=64/dt=0.01/Lx=0Ly=0/N_*num_sim_200cL_0.2iter_*.txt")
    linear_x = [1.5, 3]
    cL_vor = []
    for path_file in files:
    	file_name = os.path.split(path_file)[1]    
        print path_file
        N = float(re.findall(r"\d+\.\d+|\d+", file_name)[0])    
	graph = PF.graph_points(path_file)         
        print graph[1]
        graph = PF.gr_n(graph, 1)
	graph = PF.gr_n_2(graph, 0) 
        
	graph = PF.normalise(PF.log_div_log, math.log, graph)                                       
        subset_graph = PF.subset_graph(linear_x[0], linear_x[1], graph)
        times = []
        num_vor = []
        PF.split_graph(times, num_vor, subset_graph)
        popt, pcov = curve_fit(lin,  times, num_vor)
        print popt[0]
        cL_vor.append([N,popt[0]])

    cL_vor = sorted(cL_vor, key = operator.itemgetter(0))

    for item in cL_vor:
        print str(item[0]) + " " + str(item[1])

def lin(x, a, b):
    return a*x + b

if __name__ == "__main__":
    main()
