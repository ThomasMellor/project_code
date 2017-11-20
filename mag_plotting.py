import numpy as np
import matplotlib.pyplot as plt
import math
from scipy.optimize import curve_fit

times = []
binder_cumulant = []

with open('./magnetism:dt=0.01num_sim=70cL=0.2,Lx,y=0.txt','r') as file:
    for line in file.readlines():
        l = line.strip().split(' ')
        times.append(l[0])
        binder_cumulant.append(l[1])


times.pop(0)
binder_cumulant.pop(0)

norm_times = []
for t in times:
    norm_times.append(float(t)/math.log(float(t)))

plt.plot(norm_times, binder_cumulant)
plt.show()
