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

fig = plt.figure()
ax = plt.subplot(111)

i=24                                                                                                          
graph = PF.graph_points("../final_binder_cumulant/N_24/dt_0.01/Lx_0Ly_0/N_24num_sim_1000cL_0.2iter_45000.txt")                                                       
graph = PF.gr_n(graph, 1)                                                                                     
graph = PF.normalise(lambda t : PF.div_log(t)/(i**2), lambda x : x, graph)                                    
times = []                                                                                                    
binder = []                                                                                                   
PF.split_graph(times, binder, graph)                                                                          
#plt.plot(times, binder, label='N=24')   

i=24                                                                                                          
graph = PF.graph_points("../new_binder_cumulant/N_24/dt_0.01/Lx_0Ly_0/N_24num_sim_500cL_0.2iter_45000.txt")  
graph = PF.gr_n(graph, 1)                                                                                     
graph = PF.normalise(lambda t : PF.div_log(t)/(i**2), lambda x : x, graph)                                    
times = []                                                                                                    
binder = []                                                                                                   
PF.split_graph(times, binder, graph)                                                                          
#plt.plot(times, binder) 

i=40                                                                                                   
graph = PF.graph_points("../final_binder_cumulant/N_40/dt_0.01/Lx_0Ly_0/N_40num_sim_300cL_0.1iter_125000.txt")
graph = PF.gr_n(graph, 1)                                                                                     
graph = PF.normalise(lambda t : PF.div_log(t)/(i**2), lambda x : x, graph)                                    
times = []                                                                                                    
binder = []                                                                                                   
PF.split_graph(times, binder, graph)                                                                          
#plt.plot(times, binder, label='N=48')  

i=48                                                                                                          
graph = PF.graph_points("../final_binder_cumulant/N_48/dt_0.01/Lx_0Ly_0/N_48num_sim_600cL_0.4iter_180000.txt")
graph = PF.gr_n(graph, 1)                                                                                     
graph = PF.normalise(lambda t : PF.div_log(t)/(i**2), lambda x : x, graph)                                    
times = []                                                                                                    
binder = []                                                                                                   
PF.split_graph(times, binder, graph)                                                                          
#plt.plot(times, binder,label='N=48, nonlinera')  


i=48                                                                                                          
graph = PF.graph_points("../final_binder_cumulant/N_48/dt_0.01/Lx_0Ly_0/N_48num_sim_400cL_0.4iter_180000.txt")
graph = PF.gr_n(graph, 1)                                                                                     
graph = PF.normalise(lambda t : PF.div_log(t)/(i**2), lambda x : x, graph)                                    
times = []                                                                                                    
binder = []                                                                                                   
PF.split_graph(times, binder, graph)                                                                          
#plt.plot(times, binder,label='N=48, nonlinera')  

i=128                                                                                                          
graph = PF.graph_points("../final_binder_cumulant/N_128/dt_0.01/Lx_0Ly_0/N_128num_sim_200cL_0.4iter_1280000.txt")                                                    
graph = PF.gr_n(graph, 1)                                                                                     
graph = PF.normalise(lambda t : PF.div_log(t)/(i**2), lambda x : x, graph)                                    
times = []                                                                                                    
binder = []                                                                                                   
PF.split_graph(times, binder, graph)                                                                          
plt.plot(times, binder, label ='N=128, 300') 

i=128                                                                                                          
graph = PF.graph_points("../final_binder_cumulant/N_128/dt_0.01/Lx_0Ly_0/N_128num_sim_150cL_0.4iter_1280000.txt")                                                    
graph = PF.gr_n(graph, 1)                                                                                     
graph = PF.normalise(lambda t : PF.div_log(t)/(i**2), lambda x : x, graph)                                    
times = []                                                                                                    
binder = []                                                                                                   
PF.split_graph(times, binder, graph)                                                                          
plt.plot(times, binder, label ='N=128') 


i=64                                                                                                          
graph = PF.graph_points("../final_binder_cumulant/N_64/dt_0.01/Lx_0Ly_0/N_64num_sim_200cL_0.4iter_320000.txt")                                                
graph = PF.gr_n(graph, 1)                                                                                     
graph = PF.normalise(lambda t : PF.div_log(t)/(i**2), lambda x : x, graph)                                    
times = []                                                                                                    
binder = []                                                                                                   
PF.split_graph(times, binder, graph)                                                                          
#plt.plot(times, binder, label='N=64, linear') 

i=64                                                                                                          
graph = PF.graph_points("../final_binder_cumulant/N_64/dt_0.01/Lx_0Ly_0/N_64num_sim_400cL_0.4iter_320000.txt")                                                
graph = PF.gr_n(graph, 1)                                                                                     
graph = PF.normalise(lambda t : PF.div_log(t)/(i**2), lambda x : x, graph)                                    
times = []                                                                                                    
binder = []                                                                                                   
PF.split_graph(times, binder, graph)                                                                          
#plt.plot(times, binder, label='N=64, linear, 400') 



i=32                                                                                                          
graph = PF.graph_points("../final_binder_cumulant/N_32/dt_0.01/Lx_0Ly_0/N_32num_sim_500cL_0.4iter_80000.txt")    
graph = PF.gr_n(graph, 1)                                                                                     
graph = PF.normalise(lambda t : PF.div_log(t)/(i**2), lambda x : x, graph)                                    
times = []                                                                                                    
binder = []                                                                                                   
PF.split_graph(times, binder, graph)                                                                          
#plt.plot(times, binder,label='N=32, cL=0.2')




i=16                                                                                                          
graph = PF.graph_points("../final_binder_cumulant/N_16/dt_0.01/Lx_0Ly_0/N_16num_sim_2000cL_0.2iter_20000.txt")
graph = PF.gr_n(graph, 1)                                                                                     
graph = PF.normalise(lambda t : PF.div_log(t)/(i**2), lambda x : x, graph)                                    
times = []                                                                                                    
binder = []                                                                                                   
PF.split_graph(times, binder, graph)                                                                          
#plt.plot(times, binder, label='N=16') 


i=16                                                                                                          
graph = PF.graph_points("../final_binder_cumulant/N_16/dt_0.01/Lx_0Ly_0/N_16num_sim_2000cL_0.2iter_20000second.txt")
graph = PF.gr_n(graph, 1)                                                                                     
graph = PF.normalise(lambda t : PF.div_log(t)/(i**2), lambda x : x, graph)                                    
times = []                                                                                                    
binder = []                                                                                                   
PF.split_graph(times, binder, graph)                                                                          
#plt.plot(times, binder) 

i=16
graph = PF.graph_points("../final_binder_cumulant/N_16/dt_0.01/Lx_0Ly_0/N_16num_sim_1000cL_0.1iter_20000.txt")
graph = PF.gr_n(graph, 1)                                                                                 
graph = PF.normalise(lambda t : PF.div_log(t)/(i**2), lambda x : x, graph)                                
times = []                                                                                                
binder = []                                                                                               
PF.split_graph(times, binder, graph)


ax.legend()
#plt.plot(times, binder)
plt.show()
