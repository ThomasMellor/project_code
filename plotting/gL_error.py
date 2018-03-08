import plotting_functions as PF                                                                               
import glob                                                                                                   
import re                                                                                                     
import os                                                                                                     
import operator        
import fnmatch 

matches = []
for root, dirnames, filenames in os.walk('../final_binder_cumulant'):
    for filename in fnmatch.filter(filenames, '*.txt'):
        matches.append(os.path.join(root, filename))
	
dic = dict() 
for path_file in matches:
    result = re.findall(r"-?\d+\.\d+|-?\d+", path_file)
    N=result[0]
    Lx=result[2]
    Ly=result[3]
    run=result[5]
    cL=result[6]
    itera=result[7]
    key = N + ',' + Lx + ',' + Ly + ',' + cL + ',' + itera
    if key not in dic:
        dic[key] = int(run)
    if key in dic:
        if int(run) > dic[key]:
            dic[key] = int(run)

for path_file in matches:
    #file_name = os.path.split(path_file)[0]
    result = re.findall(r"-?\d+\.\d+|-?\d+", path_file)
    if( int(result[4]) == 2 or int(result[4]) == 4):
        continue 
    N=result[0]
    Lx=result[2]
    Ly=result[3]
    run=result[5]
    cL=result[6]
    itera=result[7]
    key = N + ',' + Lx + ',' + Ly + ',' + cL + ',' + itera
    print N
    print Lx
    print Ly
    print run
    print cL
    print itera
    directory = "../gL_error/N_" + N + "/dt_0.01/Lx_" + Lx + "Ly_" + Ly 
    print directory
    save_path = path_file.replace("final_binder_cumulant", "gL_error")
    mag2_path = path_file.replace("N_" + N + "num_sim", "mag_2N_" + N + "num_sim")
    mag4_path = path_file.replace("N_" + N + "num_sim", "mag_4N_" + N + "num_sim")
    if not os.path.exists(directory):
        os.makedirs(directory)
    mag2 = PF.graph_points(mag2_path)
    mag4 = PF.graph_points(mag4_path)    
    err_graph = PF.error_graph(mag2, mag4, int(run)) 
    PF.write_file(save_path, err_graph)
