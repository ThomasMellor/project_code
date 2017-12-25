#!/bin/bash

for i in 16
	do	
		iter=20000
		touch "file_directories4.txt"
		echo "./sim_scripts/new_simulations/N_$i/Lx_1Ly_1/cL_0.2iter_$iter"  > "file_directories4.txt"    
		mkdir -p "./new_binder_cumulant/N_$i/dt_0.01/Lx_1Ly_1"
		echo "./new_binder_cumulant/N_$i/dt_0.01/Lx_1Ly_1"   >> "file_directories4.txt"
		echo "N_${i}num_sim_200cL_0.2iter_$iter.txt" >> "file_directories4.txt"	
		./mag_analysis < "file_directories4.txt"

	done
