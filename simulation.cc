#include "simulation.h"
#include "system.h"
#include "updater.h"
#include <iostream>
#include <fstream>
#include <string>

void update_progress_bar(int, sim_parameters&, int&);

void simulate(lattice& lat, parameters& par, sim_parameters& sim_par, std::string dir, int sim_number) {
	int counter = sim_par.num_per_save;
	int files_saved = 0;
	int progress_counter = 1;

	lattice new_lat(lat.size());
	for(int iteration_num = 0; iteration_num < sim_par.num_iter; iteration_num++) {
		update_progress_bar(iteration_num, sim_par, progress_counter);

		new_lat = update_lattice(lat, par, sim_par.dt);
		if(counter == sim_par.num_per_save) {
			files_saved++;
			counter = 0;
			std::string path = dir + "/" + dir +  std::to_string(sim_number) + "," 
				+ std::to_string(iteration_num + 1) + ".txt";
			std::ofstream file(path);
			for(int j = 0; j < lat.size(); j++) {
				for(int k = 0; k < lat.size(); k++) {
					file << lat.point(j, k) << " "; 
				};	
				file << std::endl;
			};
		};
		iteration_num++;
		counter++;
		lat = new_lat;		
	};	
};

void multiple_simulate(lattice& lat, parameters& par, sim_parameters& sim_par, std::string dir) {
	for(int i = 0; i < sim_par.num_sim; i++) {
		std::cout << "Simulation " << i+1 << ":" << std::endl;
		simulate(lat, par, sim_par, dir, i+1);
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

int main() {
	lattice lat(64);
	for(int i = 0; i < 2; i++) {
		for(int j = 0; j < 2; j++) {
			lat.set(i, j, i+j);
		};
	};
	parameters param(1,1,1,1,0);
	sim_parameters sim_param(1,400,20,10);
	multiple_simulate(lat, param, sim_param, "testdir");
};
	
