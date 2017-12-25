import numpy as np
import matplotlib.pyplot as plt
import math
from scipy.optimize import curve_fit
import plotting_functions as PF 
nums = [0.001]

#i=32
#for j in nums:
#    it  = int(i*120*i*0.01/j)
#    istr = str(i)
#    dtstr = str(j)
#    its = str(it)

#    graph = PF.graph_points("../binder_cumulant/N=" + istr +"/dt="+ dtstr +"/Lx=0Ly=0/N_" + istr + "num_sim_200cL_0.2iter=" + its + ".txt") 
#    graph = PF.gr_n(graph, 1)
#    graph = PF.normalise(lambda t : PF.div_log(t)/(i**2), lambda x : x, graph) 
#
#    times = []
#    binder = []
#    PF.split_graph(times, binder, graph)
#    plt.plot(times, binder)

#i=32
#nums=[0.01]
#for j in nums:
#    it  = int(i*120*i*0.01/j)
#    istr = str(i)
#    dtstr = str(j)
#    its = str(it)
#
#    graph = PF.graph_points("../binder_cumulant/N=" + istr +"/dt="+ dtstr +"/Lx=0Ly=0/N_" + istr + "num_sim_200cL_0.2iter=" + its + ".txt") 
#    graph = PF.gr_n(graph, 1)
#lsa_output.usb-1130_USB_AUDIO-00.analog-stereo    graph = PF.normalise(lambda t : PF.div_log(t)/(i**2), lambda x : x, graph) 
#
#    times = []
#    binder = []
#    PF.split_graph(times, binder, graph)
#    plt.plot(times, binder)

i=24                                                                                                          
graph = PF.graph_points("../new_binder_cumulant/N_24/dt_0.01/Lx_0.2Ly_0.2/N_24num_sim_500cL_0.2iter_45000.txt")                                                          
graph = PF.gr_n(graph, 1)                                                                                     
graph = PF.normalise(lambda t : PF.div_log(t)/(i**2), lambda x : x, graph)                                    
times = []                                                                                                    
binder = []                                                                                                   
PF.split_graph(times, binder, graph)                                                                          
#plt.plot(times, binder)   

i=24                                                                                                          
graph = PF.graph_points("../newtestmag/cLtest24.txt")    
graph = PF.gr_n(graph, 1)                                                                                     
graph = PF.normalise(lambda t : PF.div_log(t)/(i**2), lambda x : x, graph)                                    
times = []                                                                                                    
binder = []                                                                                                   
PF.split_graph(times, binder, graph)                                                                          
#plt.plot(times, binder) 

i=32
graph = PF.graph_points("../newtestmag/cLtest32") 
graph = PF.gr_n(graph, 1)                                                                                
graph = PF.normalise(lambda t : PF.div_log(t)/(i**2), lambda x : x, graph)                               
times = []                                                                                               
binder = []                                                                                              
PF.split_graph(times, binder, graph)                                                                     
#plt.plot(times, binder)       

i=16                                                                                                          
graph = PF.graph_points("../newtestmag/finaltest16.txt")                                                 
graph = PF.gr_n(graph, 1)                                                                                     
graph = PF.normalise(lambda t : PF.div_log(t)/(i**2), lambda x : x, graph)                                    
times = []                                                                                                    
binder = []                                                                                                   
PF.split_graph(times, binder, graph)                                                                          
#plt.plot(times, binder) 

i=16
graph = PF.graph_points("../new_binder_cumulant/N_16/dt_0.01/Lx_1Ly_1/N_16num_sim_200cL_0.2iter_20000.txt") 
graph = PF.gr_n(graph, 1)                                                                                 
graph = PF.normalise(lambda t : PF.div_log(t)/(i**2), lambda x : x, graph)                                
times = []                                                                                                
binder = []                                                                                               
PF.split_graph(times, binder, graph)                                                                      
plt.plot(times, binder)
plt.show()
