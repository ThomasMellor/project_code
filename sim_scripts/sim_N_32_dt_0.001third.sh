#!/bin/bash

for i in 32  
	do
		config_file="../config_files/config_N_32_dt_0.001.txt"
		input_file="../dir_files/dir_N_32_dt_0.001.txt"
		iter=$((${i}*${i}*120*10))
		save=$((1000*${i}/16))

		echo $config_file > $input_file	
		mkdir -p "simulations/N=$i/Lx=0Ly=0/cL=0.2iter=$iter"
		echo "simulations/N=$i/Lx=0Ly=0/cL=0.2iter=$iter" >> $input_file    
		sed -i -r "s/iterations=[0-9]+/iterations=$iter/g" "./$config_file"
		sed -i -r "s/size=[0-9]+/size=$i/g" "./$config_file"
		sed -i -r "s/save=[0-9]+/save=$save/g" "./$config_file"
 		for j in 160   
			do
				sed -i -r "s/previous simulations=[0-9]+/previous simulations=$j/g" "./$config_file"
				output_file="../output_files/output_N_32_dt_0.001_prev_$j.txt"
				touch $output_file
				cat $config_file
				cat $input_file
				"../run_new_config" < $input_file   
			done

	done
