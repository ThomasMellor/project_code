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
counter=0

lam = [[0,0],[0.2,0.2],[0.2,-0.2],[0.4,0.4],[0.4,-0.4],[0.6,-0.6],[0.6,0.6],[0.8,0.8],[0.8,-0.8],[1,1],[1,-1]]

colours = {40: 'red', 64: 'blue', 48: 'green', 128: 'orange', 72: 'gray', 104: 'black'}
sizes = [40,48, 64, 128, 72, 104]
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

size_bool = False 

for item in matches:
    print item 
for lambdas in lam:
    print lambdas

with open('../tex_files/gL.tex','w') as main_file:
    with open('../tex_files/preamble.tex','r') as preable:
        for line in preable:
            main_file.write(line)
    prev_lam = 0
    for lambdas in lam:
        for path_file in matches:
            result = re.findall(r"-?\d+\.\d+|-?\d+", path_file)
            if( int(result[4]) == 2 or int(result[4]) == 4):
                continue 
            N=result[0]
            if int(N) not in sizes:
                continue
            Lx=result[2]
            Ly=result[3]
            if float(Lx) != lambdas[0] or float(Ly) != lambdas[1]:
                continue
            run=result[5]
            cL=result[6]
            if float(cL)!= 0.2:
                continue
            itera=result[7]
            key = N + ',' + Lx + ',' + Ly + ',' + cL + ',' + itera
            if dic[key] != int(run):
                continue
            
            if(prev_lam != lambdas):
                if(size_bool == True):
                    with open('../tex_files/end.tex','r') as end:
                        for line in end:
                            main_file.write(line)
                else:
                    size_bool = True
                counter+=1
            
                if(counter==3):
                    main_file.write('\\clearpage\n')
                    counter=0
                with open('../tex_files/begin.tex','r') as begin:
                    for line in begin:
                        main_file.write(line) 
                    title = '\t\ttitle={Binder cumulant for $\\lambda_x$= ' + Lx + ', $\\lambda_y$=' + Ly + ', $c_L$=' + cL + '.},\n' 
                    main_file.write(title)
                    with open('../tex_files/body_t.tex', 'r') as body:
                        for line in body:
                            main_file.write(line) 
            add_plot =  '\t\t\\addplot[mark=none, color= ' + colours[int(N)] + ']\n'
            main_file.write(add_plot)
            table='\ttable{' + path_file + '};\n'
            main_file.write(table)
            legend = '\\addlegendentry{$N$=' + N + ', ' + run + ' runs.}\n'  
            main_file.write(legend)
            prev_lam = lambdas 
    with open('../tex_files/end.tex','r') as end:
        for line in end:
            main_file.write(line)
    
    main_file.write('\\end{document}')
