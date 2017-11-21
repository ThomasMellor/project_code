import numpy as np
import matplotlib.pyplot as plt
import math
from scipy.optimize import curve_fit
import plotting_functions as PF 


graph = PF.graph_points("../binder_cumulant/N=64/dt=0.01/Lx=0Ly=0/num_sim=20cL=0.2iter=40000.txt") 
graph = PF.gr_n(graph, 1)
graph = PF.normalise(PF.div_log, PF.iden, graph)

times = []
binder = []
PF.split_graph(times, binder, graph)

plt.plot(times, binder)
plt.show()
