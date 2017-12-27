#include <iostream>
#include "simulation_utility.h"
#include "lattice_io.h"
#include "magnetisation.h"

int main() {
    std::cout << "Welcome to the magnetisation data extraction. Please type the directory where the files "
			  << "that has the simulation results:" << std::endl;
    std::string read_directory;
    getline(std::cin, read_directory);
    check_dir(read_directory);

    std::cout << "Please type the directory in which to save the file:" << std::endl;
    std::string write_directory;
    getline(std::cin, write_directory);        
    check_dir(write_directory);       
    std::vector<std::string> file_vec = list_files(read_directory); 
    if(!check_files_exist(file_vec)){
            std::cerr << "No files!" << std::endl;
            exit(1);
    }; 
	std::cout << file_vec.size();
    std::cout << "Please type in the file you want to name this:" << std::endl;
    std::string file_name;
    getline(std::cin, file_name);

	std::cout << "This is a magnetisation data extraction from directory " << read_directory
		      << " and saved in " << write_directory << "/" << file_name << std::endl;

	std::vector<std::map<double, av_magnetisation>> mag_map_list = make_magnetisation_map(file_vec, {2,4});
    
    std::map<double, double> binder_cumulant_map = make_binder_cumulant_map(mag_map_list[0], mag_map_list[1]);
    write_binder_cumulant(binder_cumulant_map, write_directory, file_name);
};
