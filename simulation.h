#ifndef SIMULATION_H
#define SIMULATION_H

#include "updater.h"
#include "fstream"
#include <string>

class sim_parameters {
	friend void simulate(int, parameters&, sim_parameters&, std::string, int);
	friend void multiple_simulate(int, parameters&, sim_parameters&, std::string);
	friend void update_progress_bar(int, sim_parameters&, int&);
	private:
		const double dt;
		const unsigned int num_iter;
		const unsigned int num_sim;
		const unsigned int num_per_save;
		const std::string init_cond;
	public: 
		sim_parameters(double timestep, int iter, int sim, int save, std::string initial) :
		   	dt(timestep), num_iter(iter), num_sim(sim), num_per_save(save), init_cond(initial) {}	
};

void simulate(int, parameters&, sim_parameters&, std::string, int);
void multiple_simulate(int, parameters&, sim_parameters&, std::string);
void update_progress_bar(int, sim_parameters&, int&);                 


#endif
