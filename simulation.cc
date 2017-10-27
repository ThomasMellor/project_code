#include "simulation.h"
#include "system.h"
#include "updater.h"
#include <iostream>
#include <fstream>
#include <string>

void simulate(lattice& lat, parameters& par, sim_parameters& sim_par, std::string dir, int sim_number) {
	int counter = sim_number;
	int files_saved = 0;
	lattice new_lat(lat.size());
	for(int i = 0; i < sim_par.num_iter; i++) {
		new_lat = update_lattice(lat, par,sim_par.dt);
		if(counter = sim_par.num_per_save) {
			files_saved++;
			counter = 1;
			std::string path = "./" + dir + "/" + dir +  std::to_string(sim_number) + "," 
				+ std::to_string(files_saved) + ".txt";
			std::ofstream file(path);
			for(int j = 0; j < lat.size(); j++) {
				for(int k = 0; k < lat.size(); k++) {
					file << lat.point(j, k) << " "; 
				};	
				file << std::endl;
			};
		};
		counter++;
		lat = new_lat;		
	};	
}

int main() {
	lattice lat(2);
	for(int i = 0; i < 2; i++) {
		for(int j = 0; j < 2; j++) {
			lat.set(i, j, i+j);
		};
	};
	parameters param(1, 1, 1, 1, 0);
	sim_parameters sim_param(1, 10, 1, 2);
	simulate(lat, param, sim_param, "testdir", 1); 
};

