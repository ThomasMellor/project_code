import numpy as np
import matplotlib.pyplot as plt
import math
from scipy.optimize import curve_fit
import plotting_functions as PF

def main():
    linear_x = [1, 4]
    graph = PF.graph_points("../vortices/N=64/dt=0.01/Lx=0Ly=0/num_sim=20cL=0.2iter=40000.txt")
    graph = PF.gr_n(graph, 1)
    print graph[0]
    graph = PF.normalise(PF.log_div_log, math.log, graph)

    #subset_graph = PF.subset_graph(linear_x[0], linear_x[1], graph)
    subset_graph = graph
    times = []
    num_vor = []
    PF.split_graph(times, num_vor, subset_graph)

    plt.plot(times, num_vor)

    popt, pcov = curve_fit(lin,  times, num_vor)
    linear_y = []
    for x in linear_x:
        linear_y.append(popt[0]*x + popt[1])

    plt.plot(linear_x, linear_y, 'b-')
    plt.show()
    print popt[0]
    print popt[1]

def lin(x, a, b):
    return a*x + b

if __name__ == "__main__":
    main()
