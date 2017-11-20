import numpy as np
import matplotlib.pyplot as plt
import math
from scipy.optimize import curve_fit

def main():
    linear_x = [1.2, 2.5]
    graph = []
    with open('./vortex:dt=0.01num_sim=20cL=0,Lx,y=0.txt','r') as file:
        for line in file.readlines():
            l = line.strip().split(' ')
            if float(l[0]) > 1:
                graph.append([math.log(float(l[0])/math.log(float(l[0]))), math.log(float(l[1]))])

    subset_graph = [[point[0], point[1]] for point in graph if 
            (point[0] > linear_x[0]) and (point[0] < linear_x[1])]

    times = []
    num_vor = []
    for point in subset_graph:
        times.append(point[0])
        num_vor.append(point[1])

    plt.plot(times, num_vor)

    popt, pcov = curve_fit(lin,  times, num_vor)
    linear_y = []
    for x in linear_x:
        linear_y.append(popt[0]*x + popt[1])

    plt.plot(linear_x, linear_y, 'b-')
    plt.show()
    #popt, pcov = curve_fit(lin, norm_times, norm_vor)
    #print popt[0]
    #print popt[1]




def lin(x, a, b):
    return a*x + b

if __name__ == "__main__":
    main()
