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
#include <map> 
#include "vortex_calculation.h"
#include "magnetisation.h"
#include <initializer_list>

/*
 * Functions related to I/O
 */

namespace fs = std::experimental::filesystem::v1;
	   
unsigned int num_words_in_string(std::string);

std::vector<std::string> list_files(std::string); // returns list of files in a directory
 
double timestep(std::string file); // returns simulation time from file name

bool check_dir_exists(std::string);

/*
 * Writes lat to path
 */
template <typename T> void lattice_write(lattice<T> const& lat, std::string  path) {	
	std::ofstream file(path);                                                                         
	for(int j = 0; j < lat.size(); j++) {                                                             
		for(int k = 0; k < lat.size(); k++) {                                                         
			file << lat.point(j, k) << " ";                                                           
		};                                                                                            
		file << std::endl;                                                                            
	};
};

/*
 * Reads path to lat 
 */
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

angle_lattice empty_angle_lattice_from_path(std::string const& path); // empty lattice of size in path

std::map<double, av_vortex_number> make_vortex_map(std::vector<std::string> const &);

std::vector<std::map<double, av_magnetisation>> make_magnetisation_map(std::vector<std::string> const&, std::initializer_list<int>);

/*
 * Writes line to line_num of lat
 */
template <typename T> void write_line(lattice<T> & lat, std::string const& line, int line_num) {
	int pos_in_line = 0; 
	std::istringstream iss(line);	
	T val;
	while(iss >> val) {
		lat.set(line_num, pos_in_line, val);
		pos_in_line++;
	};	
};


/*
 * Write binder map to file
 */
void write_binder_cumulant(std::map<double, double> const&, std::string const&, std::string const&);

/*
 * Write vortex map to file
 */
void write_vortex_number(std::map<double, av_vortex_number> const&, std::string const&, std::string const&);


#endif
