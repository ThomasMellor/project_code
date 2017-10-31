#include "simulation.h"
#include "system.h"
#include "updater.h"
#include <iostream>
#include <fstream>
#include <string>
#include "lattice_io.h"
#include "initial_condition.h"

void update_progress_bar(int, sim_parameters&, int&);

void simulate(int lattice_size, parameters& par, sim_parameters& sim_par, std::string dir, int sim_number) {
	int counter = sim_par.num_per_save;
	int files_saved = 0;
	int progress_counter = 1;
	angle_lattice lat(lattice_size);
	if(sim_par.init_cond == "disordered") {
		angle_lattice lat = disordered(lattice_size);
		
	};
	angle_lattice new_lat(lattice_size);

	for(int iteration_num = 0; iteration_num < sim_par.num_iter; iteration_num++) {
		update_progress_bar(iteration_num, sim_par, progress_counter);

		new_lat = update_lattice(lat, par, sim_par.dt);
		if(counter == sim_par.num_per_save) {
			files_saved++;
			counter = 0;
			std::string path = dir + "/" + dir +  std::to_string(sim_number) + "," 
				+ std::to_string(iteration_num + 1) + ".txt";
			lattice_write(lat, path);
		};
		iteration_num++;
		counter++;
		lat = new_lat;		
	};	
};

void multiple_simulate(int lattice_size, parameters& par, sim_parameters& sim_par, std::string dir) {
	for(int i = 0; i < sim_par.num_sim; i++) {
		std::cout << "Simulation " << i+1 << ":" << std::endl;
		simulate(lattice_size, par, sim_par, dir, i+1);
		std::cout << std::endl;
	};
};

void update_progress_bar(int iteration_num, sim_parameters& sim_par, int& progress_counter) {                 
	if(iteration_num == 0){                                                                                   
		std::cout << "[";                                                                                     
	};                                                                                                        
	if(( (double) iteration_num)/sim_par.num_iter*10 > progress_counter) {                                    
		std::cout << "#" << std::flush;                                        
		progress_counter++;                                                                                   
	};                                                                                                        
	if(iteration_num == (sim_par.num_iter - 1)){                                                                
		std::cout << "]" << std::flush;                                                                           
	};                                                                                                        
};
/*
int main() {
	angle_lattice lat(3);
	for(int i = 0; i < 2; i++) {
		for(int j = 0; j < 2; j++) {
			lat.set(i, j, i+j);
		};
	};
	parameters param(1,1,1,1,0);
	sim_parameters sim_param(1,10,20,5, "th");
	multiple_simulate(2, param, sim_param, "testdir");
};
*/	
