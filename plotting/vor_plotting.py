import numpy as np
import matplotlib.pyplot as plt
import math
from scipy.optimize import curve_fit
import plotting_functions as PF

def main():
    linear_x = [1.5, 3.5]
    graph = PF.graph_points("../test_new_vortex_analysis/test1.txt")
    graph = PF.gr_n(graph, 1)
    graph = PF.gr_n_2(graph, 0) 

    graph = PF.normalise(PF.log_div_log, math.log, graph)                                       
    subset_graph = PF.subset_graph(linear_x[0], linear_x[1], graph)
    times = []
    num_vor = []
    PF.split_graph(times, num_vor, subset_graph)
    print len(times)
    print len(num_vor)
    popt, pcov = curve_fit(lin,  times, num_vor)
    times2  = []
    num_vor2 = []

    PF.split_graph(times2, num_vor2, graph)    
    plt.plot(times2, num_vor2)
    axes = plt.gca()

    linear_y = []
    for x in linear_x:
        linear_y.append(popt[0]*x + popt[1])
    
    plt.title('vortices, linear, N=16, '+ str(popt[0])) 
    print "The gradient is ", popt[0], " +-",pcov[0][0] 
    print "The y intercept is ", popt[1], "+-", pcov[1][1]
    plt.show()

def lin(x, a, b):
    return a*x + b

if __name__ == "__main__":
    main()
