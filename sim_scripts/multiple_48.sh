#!/bin/bash

config_file="../config_files/config_N_48_dt_0.01.txt"
for i in  500 520 540 560 580        
	do
		sed -i -r "s/previous simulations=[0-9]+/previous simulations=$i/g" $config_file
		sleep 3
		gnome-terminal -x sh -c "./sim_N_48.sh; bash"
		sleep 3
	done

