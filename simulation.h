#ifndef SIMULATION_H
#define SIMULATION_H

#include "updater.h"
#include "fstream"
#include <string>

class sim_parameters {
	friend void simulate(lattice&, parameters&, sim_parameters&, std::string, int);
	friend void multiple_simulate(lattice&, parameters&, sim_parameters&, std::string);
	friend void update_progress_bar(int, sim_parameters&, int&);
	private:
		double dt;
		int num_iter;
		int num_sim;
		int num_per_save;
	public: 
		sim_parameters(int timestep, int iter, int sim, int save) : dt(timestep), num_iter(iter), num_sim(sim),
		num_per_save(save) {}	
};

void simulate(lattice&, parameters&, sim_parameters&, std::string, int);

void multiple_simulate(lattice&, parameters&, sim_parameters&, std::string);

void update_progress_bar(int, sim_parameters&, int&);                 


#endif
