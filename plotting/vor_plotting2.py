import numpy as np
import matplotlib.pyplot as plt
import math
from scipy.optimize import curve_fit
import plotting_functions as PF
import glob
import re
import os
import operator 

def main():
    grdt_tab= []
    linear_x = [0.5, 3] 
    files = glob.glob("../vortices/N=64/dt=0.02/Lx=0Ly=0/num_sim_200cL=*iter=40000.txt")
    for path_file in files:
        file_name = os.path.split(path_file)[1]
        print file_name
        cL = float(re.findall(r"\d+\.\d+|\d+", file_name)[1])
        graph = PF.graph_points(path_file)
        graph = PF.gr_n(graph, 1)
        graph = PF.normalise(PF.log_div_log, math.log, graph)

        subset_graph = PF.subset_graph(linear_x[0], linear_x[1], graph)
        times = []
        num_vor = []
        PF.split_graph(times, num_vor, subset_graph)
        popt, pcov = curve_fit(lin,  times, num_vor)

        linear_y = []
        for x in linear_x:
            linear_y.append(popt[0]*x + popt[1])

        plt.plot(linear_x, linear_y, 'b-')
        grdt_tab.append([cL, popt[0]])

    grdt_tab = sorted(grdt_tab, key = operator.itemgetter(0))

    for item in grdt_tab:
        print item[0], " ", item[1]

def lin(x, a, b):
    return a*x + b

if __name__ == "__main__":
    main()
