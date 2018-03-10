#include "system.h"
#include "vortex_calculation.h"
#include "lattice_io.h"
#include "sstream"
#include "simulation_utility.h"

int main() {

std::cout << "Welcome to the vortex location extraction. Please type the directory where the files "
                  << "that has the simulation results:" << std::endl;
        std::string read_directory;
        getline(std::cin, read_directory);
        check_dir(read_directory);

        std::cout << "Please type the directory in which to save the files:" << std::endl;
        std::string write_directory;
        getline(std::cin, write_directory);
        check_dir(write_directory);
        std::vector<std::string> file_vec = list_files(read_directory);
        if(!check_files_exist(file_vec)){
                std::cerr << "No files!" << std::endl;
                exit(1);
        };

		std::cout << "Please type in the simulation number:" << std::endl;
		std::string sim_num_str;
		getline(std::cin, sim_num_str);
		std::stringstream sim_num_ss(sim_num_str);
		int sim_num = 0;
		sim_num_ss >> sim_num;	
		std::cout << "We will perform vortex location analysis from directory " << read_directory 
				  << " and save the results to " << write_directory <<  std::endl;
		vortex_lattice vor_lat = empty_vortex_lattice_from_path(file_vec[0]);
		angle_lattice  ang_lat = empty_angle_lattice_from_path(file_vec[0]);
		std::string dt = std::to_string(deltat(file_vec[0]));	
		for(std::string file : file_vec) {
			if(simulation_number(file) != sim_num) {
				continue;
			};
			lattice_read(ang_lat, file);	
			vor_lat.set_vortex_lattice(ang_lat);
			std::stringstream stream(file);
			std::string file_name = write_directory +  "/vortex_loc:dt," + dt + ",iter_num," + std::to_string(iteration(file)) + ",sim_num," + sim_num_str + ".txt"; 
			lattice_write(vor_lat, file_name);	
		};
};
