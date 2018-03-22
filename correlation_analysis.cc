#include <iostream>
#include "simulation_utility.h"
#include "lattice_io.h"
#include "correlation.h"
template <typename T> void value_save(std::string name, T& val) {
    std::cout << name << ": ";

    std::string line;
    while(std::getline(std::cin, line)){
                std::istringstream is {line};
                if((is >> val) && !(is >> line)){
                        break;
                };
                std::cerr << "Invalid input. Please try again: ";
    };
};


int main() {
    std::cout << "Welcome to the correlation data extraction. Please type the directory where the files "
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
    double time;
    value_save("timestep:", time);
    std::cout << "Please type in the file you want to name this:" << std::endl;
    std::string file_name;
    getline(std::cin, file_name);

	std::cout << "This is a correlation data extraction from directory " << read_directory
		      << " and saved in " << write_directory << "/" << file_name << std::endl;

	std::map<int, av_correlation> cor_map = make_correlation_map(file_vec, time);
	write_correlation(cor_map, write_directory,  file_name);
};
