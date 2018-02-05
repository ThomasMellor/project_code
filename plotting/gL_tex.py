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
with open('../tex_files/gL.tex','w') as main_file:
    with open('../tex_files/preamble.tex','r') as preable:
        for line in preable:
            main_file.write(line)
    for path_file in matches:
        counter+=1
        if(counter==3):
            main_file.write('\\clearpage\n')
            counter=0
        result = re.findall(r"-?\d+\.\d+|\d+", path_file)
        if( int(result[4]) == 2 or int(result[4]) == 4):
            continue 
        with open('../tex_files/begin.tex','r') as begin:
            for line in begin:
                main_file.write(line) 
        N=result[0]
        Lx=result[2]
        Ly=result[3]
        run=result[5]
        cL=result[6]
        itera=result[7]
        title = '\t\ttitle={Binder cumulant for $N$=' + N + ', $\\lambda_x$= ' + Lx + ', $\\lambda_y$=' + Ly + ', $c_L$=' + cL + ', ' + run + ' runs.},\n' 
        main_file.write(title)
        with open('../tex_files/body_t.tex', 'r') as body:
            for line in body:
                main_file.write(line)
        table='\ttable{' + path_file + '};\n'
        main_file.write(table)
        with open('../tex_files/end.tex','r') as end:
            for line in end:
                main_file.write(line)
    main_file.write('\\end{document}')
