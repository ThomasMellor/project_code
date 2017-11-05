#ifndef LATTICE_IO_H
#define LATTICE_IO_H
#include <fstream> 
#include <iostream>
#include <iterator>
#include <string>
#include <vector>
#include "system.h"
#include <experimental/filesystem>
#include <sys/stat.h>
#include <unordered_map> 
#include "vortex_calculation.h"
#include "magnetisation.h"

namespace fs = std::experimental::filesystem::v1;
	   
unsigned int num_words_in_string(std::string);

std::vector<std::string> list_files(std::string);
 
double timestep(std::string file);

bool check_dir_exists(std::string);

template <typename T> void lattice_write(lattice<T> const& lat, std::string  path) {	
	std::ofstream file(path);                                                                         
	for(int j = 0; j < lat.size(); j++) {                                                             
		for(int k = 0; k < lat.size(); k++) {                                                         
			file << lat.point(j, k) << " ";                                                           
		};                                                                                            
		file << std::endl;                                                                            
	};
};

template <typename T> void lattice_read(lattice<T>& lat, std::string const& path) {
	std::ifstream file(path);
	if(!file) {
		std::cerr << "Error opening file" << std::endl;
		exit(1);
	};
	std::string line;
	int line_num = 0;
	getline(file, line);
	if(num_words_in_string(line) != lat.size()) {
		std::cerr << "Cannot read data onto lattice as incorrect size. " << std::endl;		
		exit(1);
	};
	write_line(lat, line, line_num);
	
	while(getline(file, line)) {
		line_num++;
		write_line(lat, line, line_num);
	};	
};

angle_lattice angle_lattice_from_path(std::string const& path);

angle_lattice empty_angle_lattice_from_path(std::string const& path);

std::unordered_map<double, av_vortex_number> make_vortex_map(std::vector<std::string> const &);

std::unordered_map<double, av_magnetisation> make_magnetisation_map(std::vector<std::string> const&, int);

template <typename T> void write_line(lattice<T> & lat, std::string const& line, int line_num) {
	int pos_in_line = 0; 
	std::istringstream iss(line);	
	T val;
	while(iss >> val) {
		lat.set(line_num, pos_in_line, val);
		pos_in_line++;
	};	
};

#endif
