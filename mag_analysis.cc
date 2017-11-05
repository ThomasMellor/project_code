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

        std::cout << "Please type in the file you want to name this:" << std::endl;
        std::string file_name;
        getline(std::cin, file_name);

        std::map<double, av_magnetisation> mag2_map = make_magnetisation_map(file_vec, 2);
        std::map<double, av_magnetisation> mag4_map = make_magnetisation_map(file_vec, 4);
        std::map<double, double> binder_cumulant_map = make_binder_cumulant_map(mag2_map, mag4_map);
        write_binder_cumulant(binder_cumulant_map, write_directory, file_name);
};
