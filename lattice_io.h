#ifndef LATTICE_IO_H
#define LATTICE_IO_D
#include <fstream> 
#include <iostream>
#include <iterator>
#include <string>
#include <vector>
#include "system.h"
#include <experimental/filesystem>
#include <sys/stat.h>

namespace fs = std::experimental::filesystem::v1;
	   
unsigned int num_words_in_string(std::string);

std::vector<std::string> list_files(std::string);
 
double timestep(std::string file);

template <typename T> void lattice_write(lattice<T> const& lat, std::string  path) {	
        struct stat sb;
        if(!(stat(path.c_str(), &sb) == 0 && S_ISDIR(sb.st_mode))){
                std::cerr << "Directory not found. Error" << std::endl;
                exit(1);
        };  
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
