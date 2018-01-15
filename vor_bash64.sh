#!/bin/bash

for i in   64 
	do
		cL=0.2
	    iter=320000
		Lx=0
		Ly=0	
		num_sim=400
		echo "./final_simulations/N_${i}/Lx_${Lx}Ly_${Ly}/cL_${cL}iter_$iter" > file_directories.txt    
		mkdir -p "./final_vortices/N_${i}/dt_0.01/Lx_${Lx}Ly_${Ly}"
		echo "./final_vortices/N_${i}/dt_0.01/Lx_${Lx}Ly_${Ly}" >> file_directories.txt
		echo "N_${i}num_sim_${num_sim}cL_${cL}iter_$iter.txt" >> file_directories.txt	
		./vortex_analysis < "file_directories.txt"

	done
