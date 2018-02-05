#!/bin/bash

for i in 64  
	do
		config_file="../config_files/config_N_64_dt_0.01.txt"
		echo $config_file
		input_file="../dir_files/dir_N_64_dt_0.01.txt"
		touch input_file
		iter=320000
		save=1600
		Lx=0.6
		Ly=0.6	
		cL=0.2
		echo $config_file > $input_file	
		mkdir -p "../final_simulations/N_$i/Lx_${Lx}Ly_${Ly}/cL_${cL}iter_${iter}"
		echo "../final_simulations/N_$i/Lx_${Lx}Ly_${Ly}/cL_${cL}iter_${iter}" >> $input_file    
		sed -i -r "s/iterations=[0-9]+/iterations=$iter/g" "./$config_file"
		sed -i -r "s/size=[0-9]+/size=$i/g" "./$config_file"
		sed -i -r "s/save=[0-9]+/save=$save/g" "./$config_file"
		sed -i -r "s/Lx=-?[0-9]\.?[0-9]*/Lx=${Lx}/g" "./$config_file"
		sed -i -r "s/Ly=-?[0-9]\.?[0-9]*/Ly=${Ly}/g" "./$config_file"
		sed -i -r "s/cL=[0-9]\.?[0-9]*/cL=${cL}/g" "./$config_file"
		"../run_new_config" < $input_file  
	done
