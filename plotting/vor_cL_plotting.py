import numpy as np                                                                                            
import matplotlib.pyplot as plt                                                                               
import math                                                                                                   
from scipy.optimize import curve_fit                                                                          
import plotting_functions as PF     
import glob
import re
import os
import operator 

cL_vor = []



files = glob.glob("../vortices/N=64/dt=0.01/Lx=0Ly=0/N_64num_sim_20cL*")
for path_file in files:
    file_name = os.path.split(path_file)[1]
    print file_name
    cL = float(re.findall(r"\d+\.\d+|\d+", file_name)[2])
    graph = PF.graph_points(path_file)
    num_vor = float(graph[-1][1])
    cL_vor.append([cL, num_vor])

cL_vor = sorted(cL_vor, key = operator.itemgetter(0))

for item in cL_vor:
    print str(item[0]) + " " + str(item[1])

cL_list = []
num_vor_list = []
PF.split_graph(cL_list, num_vor_list, cL_vor)


plt.plot(cL_list, num_vor_list)
plt.show()

    
