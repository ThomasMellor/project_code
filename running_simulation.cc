#include <iostream>
#include "simulation.h"
#include <sstream>
#include <string>

template <typename T> bool value_check(std::string line, T&val) {
        std::istringstream is {line};
        if((is >> val) && !(is >> line)){
                return true;
        } else {
                return false;
        };
};

template <typename T> void value_save(std::string name, T& val) {                                                                  
	std::cout << name << ": ";	
	
	std::string line;
	while(std::getline(std::cin, line)){
		std::istringstream is {line};
		if(value_check(line, val)){
			break;
		};
		std::cerr << "Invalid input. Please try again: ";
	};
};

int main() {
	std::cout << "Welcome to the KPZ simulation. Type in values for the following parameters:" <<std::endl;	
	double Dx;
	value_save("Dx", Dx);	
	double Dy;
	value_save("Dy", Dy);
	double Lx; 
	value_save("Lx", Lx);
	double Ly;
	value_save("Ly", Ly);
	double cL;
	value_save("cL", cL);
	double dt;
	int lat_size;
	value_save("Lattice size", lat_size);
	check_sign(lat_size);
	value_save("dt", dt);
	check_sign(dt);
	int num_iter;
	value_save("Number of iterations", num_iter);
	check_sign(num_iter);
	int num_sim;
	value_save("Number of simulations", num_sim);
	check_sign(num_sim);
	int num_save;
	value_save("Number of iterations per save", num_save);
	check_sign(num_save);
	
	std::string cond_input;
	std::string init_cond = {"ordered"};

	value_save("Disordered initial condition? ", cond_input);
	if(cond_input == "y") {
		init_cond = "disordered";
	};
	std::string directory;
	std::cout << "Please enter the directory you will be saving the files in" << std::endl;
	
	std::getline(std::cin, directory);
	
	parameters param(Dx, Dy, Lx, Ly, cL);
	sim_parameters sim_param(dt, num_iter, num_sim, num_save, init_cond);
	
	std::cout << "This is a simulation with parameters: Dx = " << Dx << ", Dy = " << Dy
		<< ", Lx = " << Lx << ", Ly = " << Ly << ", cL = " << cL << std::endl;
	std::cout << "The simulation parameters are: timestep is " << dt << ", number of iterations is "  
		<< num_iter << ", the number of simulations is " << num_sim 
		<< ", and the number of iterations per save is " << num_save << std::endl; 	
	std::cout << "The initial condition is " << init_cond << " and the directory the files will be save in is "
	<< directory << std::endl; 	

	multiple_simulate(lat_size, param, sim_param, directory);  
};
