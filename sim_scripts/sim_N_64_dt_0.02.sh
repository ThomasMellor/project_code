#!/bin/bash

for i in 64  
	do
		config_file="config_N_${i}_dt_0.02.txt"
		echo $config_file
		input_file="dir_N_${i}_dt_0.02.txt"
		touch input_file
		iter=$((${i}*${i}*60))
		save=$((200*${i}/16))

		echo $config_file > $input_file	
		mkdir -p "simulations/N=$i/Lx=0Ly=0/cL=0.2iter=$iter"
		echo "simulations/N=$i/Lx=0Ly=0/cL=0.2iter=$iter" >> $input_file    
		sed -i -r "s/iterations=[0-9]+/iterations=$iter/g" "./$config_file"
		sed -i -r "s/size=[0-9]+/size=$i/g" "./$config_file"
		sed -i -r "s/save=[0-9]+/save=$save/g" "./$config_file"
 		for j in 0 
			do
				echo $j
				sed -i -r "s/previous simulations=[0-9]+/previous simulations=$j/g" "./$config_file"
				output_file="./output_N_32_dt_0.01_prev_$j.txt"
				touch $output_file
				"./run_with_config" < $input_file  
			done

	done
