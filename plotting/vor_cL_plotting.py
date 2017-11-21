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

files = glob.glob("../vortices/N=64/dt=0.01/Lx=0Ly=0/num_sim=20cL=[01].[012345678]iter=40000.txt")
for path_file in files:
    print path_file
    file_name = os.path.split(path_file)[1]
    cL = float(re.findall(r"\d+\.\d+|\d+", file_name)[1])
    graph = PF.graph_points(path_file)
    num_vor = float(graph[-1][1])
    cL_vor.append([cL, num_vor])

cL_vor = sorted(cL_vor, key = operator.itemgetter(0))

cL_list = []
num_vor_list = []
PF.split_graph(cL_list, num_vor_list, cL_vor)


plt.plot(cL_list, num_vor_list)
plt.show()

    
