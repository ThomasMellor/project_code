#!/bin/bash

for i in  64  
	do
		temp=$((${i}*${i}*120))
		temp2=$((100*${i}/16))
		echo "sim_config_base.txt" > "file_directories.txt"	
		mkdir -p "simulations/N=$i/Lx=0Ly=0/cL=0.2iter=$temp"
		echo "simulations/N=$i/Lx=0Ly=0/cL=0.2iter=$temp" >> "file_directories.txt"    
		sed -i -r "s/iterations=[0-9]+/iterations=$temp/g" "./sim_config_base.txt"
		sed -i -r "s/size=[0-9]+/size=$i/g" "./sim_config_base.txt"
		sed -i -r "s/save=[0-9]+/save=$temp2/g" "./sim_config_base.txt"
 		"./run_with_config" < "file_directories.txt"  

	done
