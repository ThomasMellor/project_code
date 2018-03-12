#!/bin/bash

for i in 104 
	do	
		Lx=0.8
		Ly=-0.8
		cL=0.2
		iter=845000
		runs_1=250
		runs_2=150
		first=""
		extension="third"
		touch "file_directories4.txt"
		echo "./final_binder_cumulant/N_$i/dt_0.01/Lx_${Lx}Ly_${Ly}" > "file_directories4.txt"
		echo "mag_2N_${i}num_sim_${runs_1}cL_${cL}iter_${iter}$first.txt" >> "file_directories4.txt"	
		echo "mag_2N_${i}num_sim_${runs_2}cL_${cL}iter_${iter}$extension.txt" >> "file_directories4.txt"
		echo "mag_4N_${i}num_sim_${runs_1}cL_${cL}iter_${iter}$first.txt" >> "file_directories4.txt"	
		echo "mag_4N_${i}num_sim_${runs_2}cL_${cL}iter_${iter}$extension.txt" >> "file_directories4.txt"
	
		echo "./final_vortices/N_$i/dt_0.01/Lx_${Lx}Ly_${Ly}" >> "file_directories4.txt"
		echo "N_${i}num_sim_${runs_1}cL_${cL}iter_${iter}$first.txt" >> "file_directories4.txt"
		echo "N_${i}num_sim_${runs_2}cL_${cL}iter_${iter}$extension.txt" >> "file_directories4.txt"
		echo $runs_1 >> "file_directories4.txt"
		echo $runs_2 >> "file_directories4.txt"
		echo "N_${i}num_sim_$((runs_1+runs_2))cL_${cL}iter_${iter}.txt" >> "file_directories4.txt"
		echo "N_${i}num_sim_$((runs_1+runs_2))cL_${cL}iter_${iter}.txt" >> "file_directories4.txt"	
		./data_averaging < "file_directories4.txt"
	done
