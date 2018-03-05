#!/bin/bash
for j in 170 180 190 200 210   
	do
 		for i in 128  
	do
		sed -i -r "s/previous simulations=[0-9]+/previous simulations=$j/g" "config_N_128.txt"
		config_file="config_N_${i}.txt"
		input_file="dir_N_${i}_dt_0.01.txt"
		touch input_file
		iter=1280000
		save=12800
		Lx=0.6
		Ly=-0.6
		cL=0.2	
		run=10
		output_file="N=${i}cL=${cL}Lx=${Lx}Ly=${Ly}prev=${j}run=${run}.txt"
		touch $output_file
		echo $output_file
		echo $config_file > $input_file	
		mkdir -p "final_simulations/N_$i/Lx_${Lx}Ly_${Ly}/cL_${cL}iter_$iter" 
		echo "final_simulations/N_$i/Lx_${Lx}Ly_$Ly/cL_${cL}iter_$iter" >> $input_file    
		sed -i -r "s/Number of simulations=[0-9]+/Number of simulations=$run/g" "./$config_file"
		sed -i -r "s/iterations=[0-9]+/iterations=$iter/g" "./$config_file" 
		sed -i -r "s/size=[0-9]+/size=$i/g" "./$config_file"
		sed -i -r "s/save=[0-9]+/save=$save/g" "./$config_file"
		sed -i -r "s/Lx=-?[0-9]+\.?[0-9]*/Lx=$Lx/g" "./$config_file"
		sed -i -r "s/Ly=-?[0-9]+\.?[0-9]*/Ly=$Ly/g" "./$config_file"
		sed -i -r "s/cL=[0-9]+\.?[0-9]*/cL=$cL/g" "./$config_file"
		"./run_new_config" < $input_file > $output_file &
	done
		sleep 2
	done
