#!/bin/bash

for i in 64 
	do	
		Lx=0.8
		Ly=-0.8
		cL=0.2
		iter=320000
		runs_1=300
		runs_2=300
		touch "file_directories4.txt"
		echo "./final_binder_cumulant/N_$i/dt_0.01/Lx_${Lx}Ly_${Ly}" > "file_directories4.txt"
		echo "mag_2N_${i}num_sim_${runs_1}cL_${cL}iter_${iter}.txt" >> "file_directories4.txt"	
		echo "mag_2N_${i}num_sim_${runs_2}cL_${cL}iter_${iter}.txt" >> "file_directories4.txt"
		echo "mag_4N_${i}num_sim_${runs_1}cL_${cL}iter_${iter}.txt" >> "file_directories4.txt"	
		echo "mag_4N_${i}num_sim_${runs_2}cL_${cL}iter_${iter}.txt" >> "file_directories4.txt"
	
		echo "./final_vortices/N_$i/dt_0.01/Lx_${Lx}Ly_${Ly}" >> "file_directories4.txt"
		echo "N_${i}num_sim_${runs_1}cL_${cL}iter_${iter}.txt" >> "file_directories4.txt"
		echo "N_${i}num_sim_${runs_2}cL_${cL}iter_${iter}.txt" >> "file_directories4.txt"
		echo $runs_1 >> "file_directories4.txt"
		echo $runs_2 >> "file_directories4.txt"
		echo "N_${i}num_sim_$((runs_1+runs_2))cL_${cL}iter_${iter}.txt" >> "file_directories4.txt"
		echo "N_${i}num_sim_$((runs_1+runs_2))cL_${cL}iter_${iter}.txt" >> "file_directories4.txt"	
		#./vortex_analysis < "file_directories.txt"
	done
